from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class PBAudioPacket(_message.Message):
    __slots__ = ("wav_filename", "samples")
    WAV_FILENAME_FIELD_NUMBER: _ClassVar[int]
    SAMPLES_FIELD_NUMBER: _ClassVar[int]
    wav_filename: str
    samples: _containers.RepeatedScalarFieldContainer[float]
    def __init__(self, wav_filename: _Optional[str] = ..., samples: _Optional[_Iterable[float]] = ...) -> None: ...
