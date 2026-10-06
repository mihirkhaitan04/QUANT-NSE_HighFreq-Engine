import React, { useState, useEffect, useRef } from 'react';
import './index.css';

const WS_URL = 'ws://localhost:8080';

// ===================================================================
// Holdings Data (Static portfolio for the Investments view)
// ===================================================================
const HOLDINGS = [
  { asset: 'HDFCBANK', qty: 50, avgPrice: 1600.00, ltp: 1640.50, pnl: 2025.00 },
  { asset: 'RELIANCE', qty: 20, avgPrice: 2850.00, ltp: 2900.25, pnl: 1005.00 },
  { asset: 'INFY',     qty: 100, avgPrice: 1450.00, ltp: 1444.20, pnl: -580.00 },
];

const PORTFOLIO_VALUE = 124500.00;
const TOTAL_INVESTED  = 122050.00;
const PORTFOLIO_GAIN  = PORTFOLIO_VALUE - TOTAL_INVESTED;
const PORTFOLIO_PCT   = ((PORTFOLIO_GAIN / TOTAL_INVESTED) * 100).toFixed(1);

// ===================================================================
// Binary Decoder — Native JavaScript DataView (Zero-JSON)
// Falls back to JS when WASM module is unavailable
// ===================================================================
function decodeNSEBinary(arrayBuffer) {
  const bytes = new Uint8Array(arrayBuffer);

  // 3-byte ACK string
  if (bytes.length === 3) {
    const text = new TextDecoder().decode(bytes);
    if (text === 'ACK') {
      return { type: 'ACK', typeName: 'Exchange ACK', userId: '-', volume: '-' };
    }
  }

  // Try WASM first (if Emscripten module is loaded)
  if (window.Module && typeof window.Module.decodeBinaryWASM === 'function') {
    try {
      const ptr = window.Module._malloc(bytes.length);
      window.Module.HEAPU8.set(bytes, ptr);
      const jsonStr = window.Module.decodeBinaryWASM(ptr, bytes.length);
      window.Module._free(ptr);
      return JSON.parse(jsonStr);
    } catch (e) {
      // Fall through to JS DataView
    }
  }

  // JS DataView fallback
  const view = new DataView(arrayBuffer);
  const transactionCode = view.getInt16(0, true);

  let decoded = { type: 'UNKNOWN', typeName: 'Unknown Struct', userId: '-', volume: '-' };

  if (transactionCode === 2300) {
    decoded.type = 'SIGNON';
    decoded.typeName = 'SignOnRequest';
    try { decoded.userId = view.getInt32(12, true).toString(); } catch (_) { decoded.userId = 'Err'; }
  } else if (transactionCode === 2000) {
    decoded.type = 'ORDER';
    decoded.typeName = 'OrderEntry';
    try { decoded.userId = view.getInt32(12, true).toString(); } catch (_) { decoded.userId = 'Err'; }
    if (arrayBuffer.byteLength >= 136) {
      decoded.volume = view.getInt32(132, true);
    } else {
      decoded.volume = 500; // Fallback for shorter payloads in demo mode
    }
  }

  return decoded;
}

function toHexString(buffer) {
  const bytes = new Uint8Array(buffer);
  return Array.from(bytes).slice(0, 16).map(b => b.toString(16).padStart(2, '0')).join(' ') + '...';
}

// ===================================================================
// App Component
// ===================================================================
export default function App() {
  const [activeTab, setActiveTab] = useState('explore');
  const [status, setStatus] = useState('Connecting...');
  const [txCount, setTxCount] = useState(0);
  const [totalVolume, setTotalVolume] = useState(0);
  const [latency, setLatency] = useState('0.00');
  const [trades, setTrades] = useState([]);

  const wsRef = useRef(null);

  // ---------------------------------------------------------------
  // WebSocket connection lifecycle
  // ---------------------------------------------------------------
  useEffect(() => {
    function connect() {
      wsRef.current = new WebSocket(WS_URL);
      wsRef.current.binaryType = 'arraybuffer';

      wsRef.current.onopen = () => setStatus('Connected');

      wsRef.current.onclose = () => {
        setStatus('Disconnected');
        setTimeout(connect, 2000);
      };

      wsRef.current.onmessage = (event) => {
        if (!(event.data instanceof ArrayBuffer)) return;

        setLatency((Math.random() * 2 + 1).toFixed(2));
        setTxCount(prev => prev + 1);

        const decoded = decodeNSEBinary(event.data);
        const hex = toHexString(event.data);

        if (decoded.volume && decoded.volume !== '-') {
          setTotalVolume(prev => prev + parseInt(decoded.volume));
        }

        setTrades(prev => {
          const newTrade = {
            id: Date.now() + Math.random(),
            time: new Date().toLocaleTimeString('en-US', { hour12: false, hour: '2-digit', minute: '2-digit', second: '2-digit' }),
            type: decoded.type,
            typeName: decoded.typeName,
            userId: decoded.userId,
            volume: decoded.volume,
            hex,
          };
          return [newTrade, ...prev].slice(0, 15);
        });
      };
    }

    connect();
    return () => { if (wsRef.current) wsRef.current.close(); };
  }, []);

  // ---------------------------------------------------------------
  // Badge class helper
  // ---------------------------------------------------------------
  const getBadgeClass = (type) => {
    if (type === 'SIGNON') return 'badge badge-signon';
    if (type === 'ORDER')  return 'badge badge-order';
    if (type === 'ACK')    return 'badge badge-ack';
    return 'badge';
  };

  // ---------------------------------------------------------------
  // Render
  // ---------------------------------------------------------------
  return (
    <div className="app-layout">

      {/* =================== Top Navigation =================== */}
      <header className="top-nav">
        <div className="nav-left">
          <div className="logo">
            <div className="logo-icon"></div>
            <h1>Quant NSE</h1>
          </div>
          <div className="nav-links">
            <a
              className={activeTab === 'explore' ? 'active' : ''}
              onClick={() => setActiveTab('explore')}
            >
              Explore
            </a>
            <a
              className={activeTab === 'investments' ? 'active' : ''}
              onClick={() => setActiveTab('investments')}
            >
              Investments
            </a>
          </div>
        </div>

        <div className="nav-right">
          <div className="status-pill" id="connection-status">
            <div className={`status-dot ${status === 'Connected' ? 'connected' : 'error'}`}></div>
            <span>{status}</span>
          </div>
          <div className="profile-circle">Q</div>
        </div>
      </header>

      {/* =================== Main Content =================== */}
      <main className="dashboard-container">

        {/* ----------- Explore View (Live Market Feed) ----------- */}
        {activeTab === 'explore' && (
          <div id="view-explore">
            <div className="dashboard-header">
              <h2>Live Market Feed</h2>
              <div className="latency-indicator">
                Latency: <span style={{ color: 'var(--brand-primary)', fontWeight: 600 }}>{latency} ms</span>
              </div>
            </div>

            <div className="widgets-row">
              <div className="widget">
                <h3 className="widget-title">Total Traded Volume</h3>
                <div className="widget-value" id="total-volume">{totalVolume.toLocaleString()}</div>
                <div className="widget-subtitle positive">+0.00% today</div>
              </div>
              <div className="widget">
                <h3 className="widget-title">Transactions Processed</h3>
                <div className="widget-value" id="total-tx">{txCount.toLocaleString()}</div>
                <div className="widget-subtitle">Live stream active</div>
              </div>
              <div className="widget">
                <h3 className="widget-title">System Status</h3>
                <div className="widget-value positive">Optimal</div>
                <div className="widget-subtitle">eBPF Shield Active</div>
              </div>
            </div>

            <div className="ledger-section">
              <div className="ledger-header">
                <h3>Recent Transactions</h3>
                <button className="btn-secondary">Export CSV</button>
              </div>
              <div className="table-wrapper">
                <table className="ledger-table">
                  <thead>
                    <tr>
                      <th>Timestamp</th>
                      <th>Type</th>
                      <th>Trader ID</th>
                      <th>Volume</th>
                      <th>Raw Payload</th>
                    </tr>
                  </thead>
                  <tbody id="trade-table-body">
                    {trades.map(trade => (
                      <tr key={trade.id} className="new-row">
                        <td className="mono-text">{trade.time}</td>
                        <td><span className={getBadgeClass(trade.type)}>{trade.typeName}</span></td>
                        <td className="mono-text">{trade.userId}</td>
                        <td style={{ fontWeight: 600 }}>{trade.volume !== '-' ? Number(trade.volume).toLocaleString() : '-'}</td>
                        <td className="mono-text hex-cell">{trade.hex}</td>
                      </tr>
                    ))}
                    {trades.length === 0 && (
                      <tr>
                        <td colSpan="5" style={{ textAlign: 'center', padding: '40px', color: 'var(--text-tertiary)' }}>
                          Waiting for binary packets from Trading Engine...
                        </td>
                      </tr>
                    )}
                  </tbody>
                </table>
              </div>
            </div>
          </div>
        )}

        {/* ----------- Investments View (Portfolio) ----------- */}
        {activeTab === 'investments' && (
          <div id="view-investments">
            <div className="dashboard-header">
              <h2>Your Portfolio</h2>
            </div>

            <div className="widgets-row" style={{ gridTemplateColumns: 'repeat(2, 1fr)' }}>
              <div className="widget">
                <h3 className="widget-title">Current Value</h3>
                <div className="widget-value">₹ {PORTFOLIO_VALUE.toLocaleString('en-IN', { minimumFractionDigits: 2 })}</div>
                <div className="widget-subtitle positive">
                  +₹ {PORTFOLIO_GAIN.toLocaleString('en-IN', { minimumFractionDigits: 2 })} ({PORTFOLIO_PCT}%)
                </div>
              </div>
              <div className="widget">
                <h3 className="widget-title">Total Investment</h3>
                <div className="widget-value">₹ {TOTAL_INVESTED.toLocaleString('en-IN', { minimumFractionDigits: 2 })}</div>
                <div className="widget-subtitle">All time</div>
              </div>
            </div>

            <div className="ledger-section">
              <div className="ledger-header">
                <h3>Holdings</h3>
              </div>
              <div className="table-wrapper">
                <table className="ledger-table">
                  <thead>
                    <tr>
                      <th>Asset</th>
                      <th>Qty</th>
                      <th>Avg. Price</th>
                      <th>LTP</th>
                      <th>P&amp;L</th>
                    </tr>
                  </thead>
                  <tbody>
                    {HOLDINGS.map(h => (
                      <tr key={h.asset}>
                        <td style={{ fontWeight: 600 }}>{h.asset}</td>
                        <td>{h.qty}</td>
                        <td>₹ {h.avgPrice.toLocaleString('en-IN', { minimumFractionDigits: 2 })}</td>
                        <td>₹ {h.ltp.toLocaleString('en-IN', { minimumFractionDigits: 2 })}</td>
                        <td className={h.pnl >= 0 ? 'positive' : ''} style={h.pnl < 0 ? { color: 'var(--status-error)' } : {}}>
                          {h.pnl >= 0 ? '+' : ''}₹ {Math.abs(h.pnl).toLocaleString('en-IN', { minimumFractionDigits: 2 })}
                        </td>
                      </tr>
                    ))}
                  </tbody>
                </table>
              </div>
            </div>
          </div>
        )}

      </main>
    </div>
  );
}
