import asyncio
import logging

from ..audio_packet import AudioPacket
from .publisher import Publisher

log = logging.getLogger(__package__)


async def main():
    pub = Publisher()
    log.info("Created publisher")

    for i in range(10):
        samples = [float(f) for f in range(i * 10, (i + 1) * 10)]
        filename = f"audio_{i:02}.wav"
        packet = AudioPacket(filename, samples)

        log.info("Publishing packet %s", packet)
        await pub.publish(packet)
        log.info("Published packet %s", packet)

    log.info("Done")


if __name__ == "__main__":
    logging.basicConfig(
        level=logging.DEBUG,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
    )
    asyncio.run(main())
