from typing import AsyncGenerator

import zmq
import zmq.asyncio

from ..audio_packet import AudioPacket


class Subscriber:
    _context: zmq.asyncio.Context
    _socket: zmq.asyncio.Socket

    def __init__(self):
        self._context = zmq.asyncio.Context()
        self._socket = self._context.socket(zmq.PULL)
        self._socket.connect("tcp://localhost:5555")

    async def subscribe(self) -> AsyncGenerator[AudioPacket, None]:
        while True:
            data = await self._socket.recv()
            yield AudioPacket.deserialize(data)
