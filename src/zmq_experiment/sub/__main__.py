import asyncio
import logging

from ..message import MessageType
from .subscriber import Subscriber

log = logging.getLogger(__package__)


async def main() -> None:
    subscriber = Subscriber()
    log.info("Created subscriber")

    async for message in subscriber.subscribe():
        log.info("Received message %s", message)

        if message.message_type == MessageType.END:
            log.info("Received END message, stopping")
            break


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
    )
    asyncio.run(main())
