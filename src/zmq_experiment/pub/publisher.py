import zmq
import zmq.asyncio

from ..message import Message


class Publisher:
    _context: zmq.asyncio.Context
    _socket: zmq.asyncio.Socket

    def __init__(self):
        self._context = zmq.asyncio.Context()
        self._socket = self._context.socket(zmq.PUSH)
        self._socket.bind("tcp://*:5555")

    async def publish(self, message: Message):
        await self._socket.send(message.serialize())
