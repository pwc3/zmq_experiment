from zmq_experiment.message import Message, MessageType


def test_message_serialization():
    message = Message(MessageType.FULL, [1.0, 1.5, 2.0, 2.5, 3.0])
    serialized = message.serialize()
    deserialized = Message.deserialize(serialized)
    assert message == deserialized
