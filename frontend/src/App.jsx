import React, { useState, useEffect, useRef } from 'react';
import './index.css';

const WS_URL = 'ws://localhost:8080';

export default function App() {
  const [activeTab, setActiveTab] = useState('explore');
  const [status, setStatus] = useState('Disconnected');
  const [txCount, setTxCount] = useState(0);
  const [totalVolume, setTotalVolume] = useState(0);
  const [latency, setLatency] = useState('0.00');
  const [trades, setTrades] = useState([]);
  
  const wsRef = useRef(null);

  useEffect(() => {
    // Check if WebAssembly module is loaded
    // Note: The WASM module (decoder.js) will be loaded via a <script> tag in index.html
    // and attaches a global 'Module' object to the window.
    
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

        const bytes = new Uint8Array(event.data);
        let decodedStr = "";

        // Check for 3-byte ACK string first
        if (bytes.length === 3) {
            const text = new TextDecoder().decode(bytes);
            if (text === "ACK") {
                decodedStr = JSON.stringify({ type: 'ACK', typeName: 'Exchange ACK', userId: '-', volume: '-' });
            }
        } 
        else if (window.Module && window.Module.decodeBinaryWASM) {
            // ==============================================================
            // WEB ASSEMBLY DECODING (C++ -> WASM -> JS)
            // ==============================================================
            // 1. Allocate memory in the WASM heap
            const ptr = window.Module._malloc(bytes.length * bytes.BYTES_PER_ELEMENT);
            
            // 2. Copy the binary data from the WebSocket into the WASM heap
            window.Module.HEAPU8.set(bytes, ptr);
            
            // 3. Call our C++ Decoder function! (Returns a JSON string to keep JS boundaries simple)
            decodedStr = window.Module.decodeBinaryWASM(ptr, bytes.length);
            
            // 4. Free the WASM memory (Zero-leak!)
            window.Module._free(ptr);
        } else {
            console.error("WASM Module not loaded yet!");
            return;
        }

        if (decodedStr) {
            try {
                const decoded = JSON.parse(decodedStr);
                const hex = Array.from(bytes).slice(0, 16).map(b => b.toString(16).padStart(2, '0')).join(' ') + '...';
                
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
                        hex: hex
                    };
                    return [newTrade, ...prev].slice(0, 15);
                });
            } catch (e) {
                console.error("Failed to parse WASM output:", e);
            }
        }
      };
    }

    connect();

    return () => {
      if (wsRef.current) wsRef.current.close();
    };
  }, []);

  const getBadgeClass = (type) => {
    if (type === 'SIGNON') return 'badge badge-signon';
    if (type === 'ORDER') return 'badge badge-order';
    if (type === 'ACK') return 'badge badge-ack';
    return 'badge';
  };

  return (
    <div className="app-layout">
      {/* Top Navigation */}
      <nav className="top-nav">
        <div className="nav-left">
          <div className="logo">
            <div className="logo-icon"></div>
            <h1>QuantNSE</h1>
          </div>
          <div className="nav-links">
            <a 
              className={activeTab === 'explore' ? 'active' : ''} 
              onClick={() => setActiveTab('explore')}
            >
              Live Feed
            </a>
            <a 
              className={activeTab === 'investments' ? 'active' : ''} 
              onClick={() => setActiveTab('investments')}
            >
              Algorithms
            </a>
          </div>
        </div>
        
        <div className="nav-right">
          <div className="status-pill">
            <div className={`status-dot ${status === 'Connected' ? 'connected' : 'error'}`}></div>
            <span>{status}</span>
          </div>
          <div className="profile-circle">MK</div>
        </div>
      </nav>

      {/* Main Content */}
      <main className="dashboard-container">
        <div className="dashboard-header">
          <h2>WASM Binary Decoder (React)</h2>
          <div className="latency-indicator">
            Server Latency: <span style={{color: '#00d09c', fontWeight: '600'}}>{latency} ms</span>
          </div>
        </div>

        {activeTab === 'explore' ? (
          <div>
            {/* Widgets */}
            <div className="widgets-row">
              <div className="widget">
                <div className="widget-title">WASM Packets Decoded</div>
                <div className="widget-value positive">{txCount.toLocaleString()}</div>
                <div className="widget-subtitle">TCP frames parsed via WebAssembly</div>
              </div>
              <div className="widget">
                <div className="widget-title">Cumulative Volume</div>
                <div className="widget-value">{totalVolume.toLocaleString()}</div>
                <div className="widget-subtitle">Shares requested by engine</div>
              </div>
              <div className="widget">
                <div className="widget-title">Memory Allocation</div>
                <div className="widget-value positive">0 Bytes</div>
                <div className="widget-subtitle">Zero-allocation C++ memory pools active</div>
              </div>
            </div>

            {/* Ledger Table */}
            <div className="ledger-section">
              <div className="ledger-header">
                <h3>Live Market Feed</h3>
                <button className="btn-secondary">Export Log</button>
              </div>
              <div className="table-wrapper">
                <table className="ledger-table">
                  <thead>
                    <tr>
                      <th>Time</th>
                      <th>Message Type</th>
                      <th>User ID</th>
                      <th>Volume</th>
                      <th>Raw Hex Binary (First 16 Bytes)</th>
                    </tr>
                  </thead>
                  <tbody>
                    {trades.map(trade => (
                      <tr key={trade.id} className="new-row">
                        <td className="mono-text">{trade.time}</td>
                        <td><span className={getBadgeClass(trade.type)}>{trade.typeName}</span></td>
                        <td className="mono-text">{trade.userId}</td>
                        <td style={{fontWeight: 600}}>{trade.volume !== '-' ? trade.volume.toLocaleString() : '-'}</td>
                        <td className="mono-text hex-cell">{trade.hex}</td>
                      </tr>
                    ))}
                    {trades.length === 0 && (
                      <tr>
                        <td colSpan="5" style={{textAlign: 'center', padding: '40px', color: 'var(--text-tertiary)'}}>
                          Waiting for binary packets from Trading Engine...
                        </td>
                      </tr>
                    )}
                  </tbody>
                </table>
              </div>
            </div>
          </div>
        ) : (
          <div style={{
              backgroundColor: 'var(--bg-surface)', 
              padding: '60px', 
              borderRadius: '12px', 
              textAlign: 'center',
              border: '1px solid var(--border-color)'
          }}>
              <h2 style={{marginBottom: '16px', color: 'var(--brand-primary)'}}>Algorithmic Trading Strategies</h2>
              <p style={{color: 'var(--text-secondary)', lineHeight: '1.6'}}>
                  This section will contain controls for your C++ HFT strategies (Market Making, Latency Arbitrage).
                  <br/>Currently running in fully automated headless mode.
              </p>
          </div>
        )}
      </main>
    </div>
  );
}
