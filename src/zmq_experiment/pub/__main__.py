import asyncio
import logging

from ..message import Message, MessageType
from .publisher import Publisher

log = logging.getLogger(__package__)


async def main():
    pub = Publisher()
    log.info("Created publisher")

    for i in range(10):
        samples = [float(f) for f in range(i * 10, (i + 1) * 10)]

        if i == 0:
            message_type = MessageType.START
        elif i == 9:
            message_type = MessageType.END
        else:
            message_type = MessageType.CONTINUE

        message = Message(message_type, samples)

        log.info("Publishing message %s", message)
        await pub.publish(message)
        log.info("Published message")

    log.info("Done")


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
    )
    asyncio.run(main())
