// Examples of binary message packing using Java

//using DataView
function packMessageWithDataView(message_type, version) {
	const buffer = new ArrayBuffer(8); // 4 bytes for message type and 4 bytes for version
	const dataView = new DataView(buffer);

	dataView.setInt32(0, message_type, true); // true for little-endian

	dataView.setInt32(4, version, true); // true for little-endian
	
	return buffer; // Return the packed buffer
}

//using Node.js
const { Buffer } = require('buffer');
function packMessageWithNode(message_type, version) {
	const buffer = Buffer.alloc(8);

	buffer.writeInt32LE(message_type, 0); // little-endian

	buffer.writeInt32LE(version, 4); // little-endian
	return buffer;
}

//testing with DataView
const packedMessageWithDataView = packMessageWithDataView(1, 3);
console.log("Packed message with DataView:", new Uint8Array(packedMessageWithDataView));

//testing with Node.js
const packedMessageWithNode = packMessageWithNode(1, 3);
console.log("Packed message with Node.js:", packedMessageWithNode);
