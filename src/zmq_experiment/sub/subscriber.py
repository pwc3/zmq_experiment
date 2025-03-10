from typing import AsyncGenerator

import zmq
import zmq.asyncio

from ..message import Message


class Subscriber:
    _context: zmq.asyncio.Context
    _socket: zmq.asyncio.Socket

    def __init__(self):
        self._context = zmq.asyncio.Context()
        self._socket = self._context.socket(zmq.PULL)
        self._socket.connect("tcp://localhost:5555")

    async def subscribe(self) -> AsyncGenerator[Message, None]:
        while True:
            data = await self._socket.recv()
            yield Message.deserialize(data)
