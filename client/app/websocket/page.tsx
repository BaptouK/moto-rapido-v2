'use client';

import { useEffect, useState } from 'react';
import {Button} from "@/components/ui/button";

export default function WebSocketPage() {
    const [socket, setSocket] = useState<WebSocket | null>(null);
    const [messages, setMessages] = useState([]);

    useEffect(() => {
        const ws = new WebSocket('ws://localhost:8080/ws');
        ws.binaryType = 'arraybuffer';

        ws.onopen = () => {
            console.log('WebSocket Connected');
        };

        ws.onmessage = (event) => {
            const data = new Uint8Array(event.data);
            console.log('Received binary data:', data);
            // setMessages((prev) => [...prev, data]);
        };

        ws.onclose = () => {
            console.log('WebSocket Disconnected');
        };

        setSocket(ws);
        return () => ws.close();
    }, []);

    const sendBinaryData = () => {
        if (socket && socket.readyState === WebSocket.OPEN) {
            const byteArray = new Uint8Array([1, 2, 3, 4, 5]);
            socket.send(byteArray);
            console.log('Sent binary data:', byteArray);
        }
    };

    return (
        <div className="p-4">
            <h1 className="text-xl font-bold">WebSocket Binary Data</h1>
            <Button onClick={sendBinaryData}>
                Send Binary Data
            </Button>
            <div className="mt-4">
                <h2 className="text-lg font-semibold">Received Messages:</h2>
                <ul>
                    {messages.map((msg, index) => (
                        <li key={index} className="text-gray-700">{JSON.stringify(Array.from(msg))}</li>
                    ))}
                </ul>
            </div>
        </div>
    );
}
