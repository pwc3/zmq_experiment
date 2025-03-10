from dataclasses import dataclass
from enum import Enum
from typing import List, cast

import numpy as np


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

        t = np.array([self.message_type.value], dtype=np.uint8)
        c = np.array([count], dtype=np.uint64)
        s = np.array(self.samples, dtype=np.float32)

        return t.tobytes() + c.tobytes() + s.tobytes()

    @classmethod
    def deserialize(cls, data: bytes) -> "Message":
        # Unpack the header
        # header_fmt = "BQ"
        # header_size = struct.calcsize(header_fmt)
        # message_type, count = struct.unpack(header_fmt, data[:header_size])

        # # Unpack the samples
        # samples = np.frombuffer(data, dtype=np.float32, offset=header_size, count=count)

        # return cls(MessageType(message_type), cast(List[float], samples.tolist()))

        offset = 0
        message_type = MessageType(
            np.frombuffer(data, dtype=np.uint8, offset=offset, count=1)
        )

        offset += 1
        count = np.frombuffer(data, dtype=np.uint64, offset=offset, count=1).item()

        offset += 8
        samples = np.frombuffer(data, dtype=np.float32, offset=offset, count=count)

        return cls(message_type, cast(List[float], samples.tolist()))
