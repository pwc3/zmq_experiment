from zmq_experiment.audio_packet import Message, MessageType


def test_message_serialize():
    source_message = Message(MessageType.START, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

    expected = (
        # Message type
        b"\x02"
        # Number of elements
        b"\x0a\x00\x00\x00\x00\x00\x00\x00"
        # Samples
        b"\x00\x00\x00\x00"
        b"\x00\x00\x80\x3f"
        b"\x00\x00\x00\x40"
        b"\x00\x00\x40\x40"
        b"\x00\x00\x80\x40"
        b"\x00\x00\xa0\x40"
        b"\x00\x00\xc0\x40"
        b"\x00\x00\xe0\x40"
        b"\x00\x00\x00\x41"
        b"\x00\x00\x10\x41"
    )

    actual = source_message.serialize()
    print("expected:", expected)
    print("actual:", actual)

    assert actual == expected


def test_message_deserialize():
    source_bytes = (
        # Message type
        b"\x02"
        # Number of elements
        b"\x0a\x00\x00\x00\x00\x00\x00\x00"
        # Samples
        b"\x00\x00\x00\x00"
        b"\x00\x00\x80\x3f"
        b"\x00\x00\x00\x40"
        b"\x00\x00\x40\x40"
        b"\x00\x00\x80\x40"
        b"\x00\x00\xa0\x40"
        b"\x00\x00\xc0\x40"
        b"\x00\x00\xe0\x40"
        b"\x00\x00\x00\x41"
        b"\x00\x00\x10\x41"
    )

    expected = Message(MessageType.START, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

    actual = Message.deserialize(source_bytes)
    assert actual == expected
