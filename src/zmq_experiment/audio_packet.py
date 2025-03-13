from dataclasses import dataclass

from .protobuf.zmq_experiment_pb2 import PBAudioPacket


@dataclass
class AudioPacket:
    wav_filename: str
    samples: list[float]

    def serialize(self) -> bytes:
        packet = PBAudioPacket(wav_filename=self.wav_filename, samples=self.samples)
        return packet.SerializeToString()

    @classmethod
    def deserialize(cls, data: bytes) -> "AudioPacket":
        packet = PBAudioPacket()
        packet.ParseFromString(data)

        return cls(packet.wav_filename, list(packet.samples))
