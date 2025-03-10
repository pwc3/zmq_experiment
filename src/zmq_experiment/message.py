import struct
from dataclasses import dataclass
from enum import Enum
from typing import List


class MessageType(Enum):
    FULL = 1
    START = 2
    CONTINUE = 3
    END = 4


@dataclass
class Message:
    message_type: MessageType
    samples: List[float]

    def __eq__(self, value: object) -> bool:
        if not isinstance(value, Message):
            return False

        return self.message_type == value.message_type and self.samples == value.samples

    def serialize(self) -> bytes:
        count = len(self.samples)
        return struct.pack(f"BN{count}f", self.message_type.value, count, *self.samples)

    @classmethod
    def deserialize(cls, data: bytes) -> "Message":
        # deserialize the type and count
        message_type, count = struct.unpack("BN", data[:16])

        # deserialize samples
        samples = struct.unpack(f"{count}f", data[16:])

        return cls(MessageType(message_type), list(samples))
