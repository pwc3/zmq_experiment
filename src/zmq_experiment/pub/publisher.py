import zmq
import zmq.asyncio

from ..audio_packet import AudioPacket


class Publisher:
    _context: zmq.asyncio.Context
    _socket: zmq.asyncio.Socket

    def __init__(self):
        self._context = zmq.asyncio.Context()
        self._socket = self._context.socket(zmq.PUSH)
        self._socket.bind("tcp://*:5555")

    async def publish(self, packet: AudioPacket):
        await self._socket.send(packet.serialize())
