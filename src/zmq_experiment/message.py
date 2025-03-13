from dataclasses import dataclass

from .protobuf.zmq_experiment_pb2 import PBAudioPacket


@dataclass
class AudioPacket:
    wav_file: str
    samples: list[float]

    def __eq__(self, value: object) -> bool:
        if not isinstance(value, AudioPacket):
            return False
        return self.wav_file == value.wav_file and self.samples == value.samples

    def serialize(self) -> bytes:
        raise NotImplementedError

    @classmethod
    def deserialize(cls, data: bytes) -> "AudioPacket":
        raise NotImplementedError
