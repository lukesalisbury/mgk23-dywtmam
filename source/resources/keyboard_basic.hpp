size_t keyboard_image_size = 2497;
size_t keyboard_sheet_size = 53;

uint8_t keyboard_image_data[2497] = { 
	0x89,0x50,0x4e,0x47,0xd,0xa,0x1a,0xa,0,0,0,0xd,0x49,0x48,0x44,0x52,0,0,0x1,0x20,
	0,0,0,0x60,0x8,0x2,0,0,0,0x32,0xce,0x38,0xf,0,0,0,0x7,0x74,0x49,0x4d,
	0x45,0x7,0xe3,0x8,0x1d,0x7,0x9,0x20,0x21,0xe4,0x8a,0xb,0,0,0,0x9,0x70,0x48,0x59,0x73,
	0,0,0xb,0x12,0,0,0xb,0x12,0x1,0xd2,0xdd,0x7e,0xfc,0,0,0,0x4,0x67,0x41,0x4d,
	0x41,0,0,0xb1,0x8f,0xb,0xfc,0x61,0x5,0,0,0,0x6,0x74,0x52,0x4e,0x53,0,0xb4,0,
	0xff,0,0x11,0x5f,0xc9,0xbd,0x5a,0,0,0x9,0x3e,0x49,0x44,0x41,0x54,0x78,0xda,0xed,0x9d,0x3f,
	0x8e,0x1d,0x45,0x10,0xc6,0x67,0xad,0xbd,0,0x42,0x88,0x4b,0x38,0xc1,0xbe,0x1,0x92,0x25,0xcb,0xe1,
	0xca,0x1,0x99,0x3,0x60,0xb9,0,0x26,0x40,0x22,0x42,0x22,0xc0,0x9c,0xc0,0x88,0x80,0x8c,0,0x39,
	0x42,0x8,0x9,0x89,0x90,0,0x61,0x48,0xb8,0x84,0x65,0xf9,0xc,0xb0,0x66,0xd6,0x4d,0xbb,0xff,0xd6,
	0xd7,0xd3,0xd5,0x5d,0xfd,0xf8,0x3e,0x21,0xf4,0xde,0xfa,0x37,0x35,0x35,0x3d,0xdd,0x33,0xb3,0x6f,0xeb,
	0x7b,0x75,0xf6,0xc3,0xdf,0x6f,0x6c,0x14,0x45,0xe9,0xe8,0xdc,0xbd,0xfa,0xeb,0xd1,0xc7,0x5,0xee,0xe6,
	0xc3,0xaf,0x82,0x9f,0x90,0x27,0x6f,0x87,0x47,0xd5,0x3d,0x9f,0x18,0xd8,0x75,0xee,0xe8,0xcb,0xf,0x3e,
	0x2a,0xec,0xe0,0xf1,0xa3,0xd7,0x42,0x90,0x27,0x6f,0x8a,0x47,0xd5,0x3d,0x9f,0x5f,0xb7,0xf4,0x2,0xbb,
	0xd1,0x31,0x69,0x8a,0x1a,0xa0,0x8b,0x8b,0xfb,0xb3,0x53,0,0xf4,0x72,0x81,0x7d,0xfb,0xde,0xbb,0x12,
	0xd4,0x61,0xe4,0xc9,0xcf,0xe2,0x3b,0xae,0x2e,0xed,0xfc,0x77,0x9d,0xcb,0x51,0x8a,0x9a,0x2b,0xb7,0xba,
	0xfc,0x65,0xf6,0xe4,0xc9,0xf7,0xb3,0xf3,0x2a,0x89,0x8f,0x88,0x14,0xa5,0x28,0xde,0xc1,0xa8,0x65,0x74,
	0x75,0xb3,0xda,0xef,0x5d,0xc6,0xef,0x5a,0xbe,0x78,0x7,0xa3,0x56,0xd2,0x42,0x4b,0x6b,0xd7,0xf5,0x2,
	0xbb,0x75,0xfb,0x9d,0x32,0x17,0,0xe4,0xc9,0xcf,0xe2,0xbb,0xac,0x31,0xed,0xfc,0x9d,0xae,0x1f,0x11,
	0xbf,0x7e,0xfc,0xcd,0x76,0x59,0xe2,0x5e,0x2,0xc1,0x5b,0xf2,0xe4,0xcd,0xf0,0xa8,0xfa,0xe7,0x93,0xf9,
	0x64,0xf1,0x7a,0x81,0xdd,0xbe,0x7d,0x2b,0x8,0x11,0xe8,0xa,0x78,0xfa,0xf4,0xf,0xff,0x2d,0x79,0xf2,
	0x76,0x78,0x54,0xdd,0xf3,0x79,0x50,0x5e,0x60,0xfb,0x36,0x68,0x8a,0xe4,0xc9,0x9b,0xe5,0x51,0x1d,0xce,
	0xe7,0x97,0x24,0x76,0xfd,0x3b,0x98,0xbf,0x3a,0x93,0xa,0,0xf2,0xe4,0x4d,0xf1,0xa8,0x86,0xe5,0x73,
	0xb6,0x57,0xd3,0x4b,0xfe,0x38,0xfd,0xe0,0xbb,0xff,0xd6,0x28,0x79,0xf2,0xd6,0x78,0x54,0x7d,0xf3,0xf1,
	0xff,0xd5,0xd7,0x19,0xed,0x2a,0x14,0xa5,0x27,0xfe,0x1d,0x8c,0xa2,0x14,0x45,0x3f,0x18,0xf9,0x53,0xe0,
	0x51,0xd,0xcb,0x9f,0x7e,0x30,0xf2,0xa7,0xc0,0xa3,0x1a,0x96,0x7f,0x9f,0x5a,0xc4,0x8b,0x8b,0xfb,0xd0,
	0xdf,0xd7,0x21,0x1e,0x2d,0x9d,0x76,0xfc,0x80,0x94,0xa0,0x4d,0x84,0x70,0x43,0xa9,0x38,0x9a,0xf,0x5a,
	0xd1,0x87,0x9e,0x5f,0x55,0x99,0x4a,0xa6,0xaa,0xe,0x7e,0xb0,0xfd,0x80,0x63,0xa3,0x4e,0x81,0x87,0xe2,
	0x6f,0xff,0x4e,0x85,0x78,0x4c,0xcb,0x3c,0x14,0x3f,0x99,0x52,0xd5,0xff,0x13,0xec,0xa5,0x1c,0x5f,0x2f,
	0xff,0x3d,0xb8,0x3c,0xbe,0xe3,0x83,0xa3,0xee,0x75,0x7e,0x73,0xfa,0xbf,0xf9,0xc1,0x76,0x6c,0x42,0x35,
	0x7d,0xf2,0x6c,0x95,0x79,0x34,0xfe,0xf8,0x83,0x2a,0x8,0xbd,0xe2,0x3a,0xd8,0xda,0x81,0x4c,0xd7,0x8a,
	0x7e,0xb0,0xf4,0x2,0x73,0x8f,0x10,0x76,0x6e,0xc7,0xcd,0x4f,0x95,0xc2,0xc8,0xd,0x97,0xc6,0x86,0xa7,
	0x3e,0x8d,0xc1,0x6c,0x30,0x71,0x98,0x72,0xdd,0xab,0xe,0xce,0x74,0x25,0x16,0x98,0x9b,0x70,0x8b,0xae,
	0xae,0xd,0xbf,0x49,0xee,0xb0,0x7c,0x2f,0x3b,0x26,0xdf,0x5,0xca,0x37,0x5c,0x20,0xe4,0xf9,0x3b,0x46,
	0x69,0x99,0xa1,0xab,0x1d,0x22,0x4f,0xc1,0xf,0xb6,0x67,0x9f,0x7c,0xac,0x9f,0x2b,0xe1,0x84,0x40,0xe7,
	0x8d,0x3b,0x52,0x53,0x77,0,0xed,0xc1,0xd7,0xbb,0x7a,0xa2,0x33,0x67,0xbf,0x94,0xb,0x87,0xd4,0xda,
	0x9c,0xac,0xaa,0x83,0x1f,0x2c,0xf9,0x24,0x59,0xe0,0xdd,0xed,0x42,0x89,0xdf,0x52,0xb,0xa0,0xbb,0xff,
	0x47,0x9e,0x4f,0xf2,0x71,0xa0,0xaf,0x3f,0xa,0x8d,0xf,0x8d,0xf,0x7a,0x7e,0x1b,0xf2,0x8f,0xd7,0xe4,
	0xea,0x7e,0x30,0x7,0xf4,0xf1,0x83,0x7d,0xfa,0xd9,0x27,0xbf,0xff,0xf9,0x9b,0x90,0xbf,0x82,0xf7,0x17,
	0xfe,0x26,0x12,0xde,0xdf,0xa4,0x63,0xfc,0xe4,0x21,0x54,0x8f,0x57,0x9e,0x8f,0xe3,0xa1,0xf8,0xf2,0xf1,
	0x6c,0x8b,0xaf,0x9a,0x4f,0xac,0xd3,0xf7,0x83,0x65,0x78,0xfa,0xc1,0xc8,0x9f,0x2,0x8f,0x6a,0x58,0xfe,
	0xf4,0x83,0x91,0x3f,0x4d,0x1e,0x95,0x52,0x3e,0xf4,0x83,0x91,0x3f,0x5,0x1e,0xd5,0xb0,0xfc,0xe9,0x7,
	0x23,0x7f,0x22,0x3c,0xaa,0x31,0xf9,0xd3,0xf,0x46,0x51,0x8a,0xa2,0x1f,0x8c,0xa2,0x14,0x25,0xf5,0x83,
	0xa1,0xb2,0xe6,0x17,0x22,0x4f,0x7e,0xa,0x2f,0xf5,0x83,0xa1,0xb2,0xe6,0x17,0x22,0x3f,0x92,0x8f,0xb,
	0x9a,0x3a,0xf2,0xc9,0x1a,0x14,0xb3,0xe3,0x93,0xad,0xa6,0xf,0xfe,0xd8,0xef,0x17,0xb0,0x25,0x2b,0xeb,
	0xd0,0xea,0x18,0xc9,0x56,0xfe,0xb8,0x7,0xfb,0xbd,0x7b,0xef,0x8e,0x24,0xf3,0x6a,0x56,0x47,0xcc,0x57,
	0xd0,0x2e,0xe4,0x75,0x74,0x68,0x6d,0x61,0xb0,0x15,0x74,0x8,0x1a,0xe3,0xd3,0x6,0x43,0x85,0x9d,0x76,
	0xaa,0x64,0xab,0xca,0xfa,0xc1,0xfc,0xa,0xbd,0x64,0x79,0x68,0xb5,0x64,0xb1,0xea,0x47,0xa,0x86,0x35,
	0xe6,0x83,0xc8,0xc1,0xb4,0xe8,0xe5,0x1f,0xcb,0x1d,0x42,0xd5,0xaf,0x25,0xf4,0x83,0xf9,0x98,0xff,0x7a,
	0x56,0x3f,0x2e,0xf9,0xf8,0x37,0x8f,0x8f,0x6a,0xfe,0x6b,0xf1,0xc0,0x87,0x1c,0x13,0x2f,0x1b,0x6d,0xbb,
	0xd6,0x2b,0x66,0xd5,0xde,0x5,0x75,0x32,0x82,0xd,0x97,0xc1,0xd,0xda,0xa6,0x7d,0,0xca,0x6a,0xc0,
	0x21,0xac,0xf5,0x54,0x13,0xc8,0xe0,0x29,0x5e,0x68,0x3c,0xb1,0x5,0x16,0x3f,0x28,0x37,0xfc,0xb6,0x80,
	0xca,0xdf,0x29,0x6a,0x79,0x92,0xc8,0x9a,0xf9,0xcd,0x9a,0x38,0x2c,0x47,0x24,0x7d,0x44,0xf4,0x1f,0xdc,
	0x47,0xe6,0x77,0x64,0x77,0xa8,0x21,0x92,0x5a,0x48,0x6d,0x26,0xf4,0xf1,0x2a,0xf9,0xc1,0x2,0x23,0x56,
	0x70,0x27,0x71,0xff,0x9a,0xbc,0xf6,0x4b,0xfc,0x4b,0xfe,0x86,0x65,0xbf,0xd,0x14,0xdf,0x4f,0x4f,0xc8,
	0xc7,0x7,0x28,0xf1,0x53,0x29,0xf1,0x6e,0x7c,0xd0,0xfc,0x95,0xc6,0x3f,0x39,0x8f,0x17,0xea,0x27,0x36,
	0x97,0x7f,0x59,0x2a,0xb5,0x7f,0xdc,0xf1,0xe1,0xe5,0xfb,0x5b,0x3f,0xed,0xc5,0xfc,0x7b,0x39,0x56,0x32,
	0xfe,0x17,0x9f,0x7f,0xb9,0x79,0xc6,0xaa,0x2a,0x8f,0xc6,0x27,0x3f,0x91,0xf,0x4e,0x6e,0x77,0xde,0xdf,
	0x70,0xdf,0xca,0xec,0xf8,0x48,0xfd,0x60,0xa8,0xaa,0xfe,0x99,0xb7,0xde,0x7e,0xf3,0xf9,0xb3,0x17,0x57,
	0x3,0x74,0xf5,0x42,0xc2,0xa3,0xf1,0xc9,0x4f,0xe4,0xf7,0x73,0xea,0xff,0xa4,0x2f,0xef,0x6f,0xb8,0xff,
	0xdc,0xec,0xf8,0xb4,0xfb,0xc1,0x50,0x59,0xf3,0xb,0x91,0x27,0x3f,0x80,0x97,0xfa,0xc1,0x50,0x59,0xf3,
	0xb,0x91,0x27,0x3f,0x85,0x7,0xfc,0x60,0xa8,0xac,0xf9,0x85,0xc8,0x93,0x1f,0xcf,0xd3,0xf,0x46,0x51,
	0x8a,0xa2,0x1f,0x8c,0xa2,0x14,0x45,0x3f,0x18,0x79,0x8b,0x3c,0x2a,0x6b,0xf9,0xd3,0xf,0x46,0xde,0x34,
	0x8f,0x6a,0x56,0xfe,0x81,0xa3,0xca,0xbd,0x96,0xfa,0xc1,0xfc,0x12,0x8a,0x82,0x13,0xac,0xad,0x5f,0x96,
	0x9c,0x6f,0xeb,0x7f,0x25,0xe4,0xf,0x5a,0xc2,0x84,0xbb,0x88,0xd,0x75,0x42,0x5e,0x1e,0x1c,0xf5,0x9b,
	0x29,0xa9,0xa1,0x59,0x9c,0x7b,0xbd,0x62,0xcd,0x5a,0xd9,0xe9,0x97,0xf6,0x83,0xc5,0x2d,0xa7,0xaa,0x4e,
	0xb0,0xb8,0x4c,0xb1,0xbb,0x7f,0x49,0xc8,0xfb,0x49,0x4a,0xfc,0x4e,0x1b,0xe8,0x1f,0x73,0xa3,0xa9,0x74,
	0xbc,0x47,0x78,0x3d,0xbf,0x99,0x6a,0x7f,0xb0,0x42,0x8d,0xab,0xbc,0xe0,0x30,0x8e,0xef,0x57,0xf3,0xb9,
	0x9f,0xb8,0xd7,0x1,0xef,0x97,0xb3,0x5,0xff,0xdf,0x5f,0x94,0xe7,0x67,0x9c,0x2d,0xe0,0x7,0xeb,0x7e,
	0xcd,0xcb,0xdd,0xc,0xb,0xfc,0xa6,0xdf,0x28,0xac,0xa1,0x21,0x88,0x9d,0x2b,0xee,0x9,0xb8,0x1,0xdc,
	0x94,0xf0,0x2b,0x5d,0xb7,0xd4,0x3a,0x9,0x30,0x49,0x64,0xc8,0xc4,0xed,0x78,0xc9,0xc4,0x2b,0x77,0xab,
	0x1,0x3e,0x45,0xc,0xea,0x97,0xfd,0x6a,0x51,0xd5,0xd2,0x66,0xb4,0xf7,0x4f,0x83,0xe4,0xa7,0xea,0xe0,
	0x2e,0x54,0x3b,0x6,0xa9,0x4a,0xa3,0x1d,0x91,0x9f,0x7f,0xf2,0x41,0xd1,0x9f,0x5d,0xb1,0x5,0xbb,0xcd,
	0x83,0x5b,0x18,0xab,0x82,0x1b,0xab,0x7a,0xb0,0x39,0xaf,0x9,0x60,0x57,0x89,0x7f,0xf5,0xa,0x1e,0x11,
	0x1b,0x5a,0x72,0xc9,0xc7,0x45,0x7b,0xd,0xb7,0x5d,0xfe,0x21,0x47,0x8c,0x9e,0xd9,0x67,0xcc,0x35,0x48,
	0x2f,0xb8,0x64,0x64,0x92,0x97,0x27,0x74,0x3c,0xcb,0x47,0x91,0x8b,0xd6,0x96,0xdb,0xae,0xfa,0x2,0xeb,
	0xee,0x4,0x43,0x3,0x1a,0xb4,0xfd,0x18,0x4c,0xa9,0xed,0xbe,0x31,0x3b,0x6b,0x20,0x9f,0x86,0x49,0xe8,
	0x7f,0x75,0x8a,0xbc,0xeb,0x5d,0x6c,0x97,0x2e,0x27,0x96,0xf4,0x73,0x39,0xa5,0xfd,0x60,0x81,0x25,0x29,
	0xe7,0x4,0x8b,0x7f,0xe8,0x24,0xef,0x4f,0xb5,0xbf,0x96,0xf8,0xbb,0xa0,0xfe,0x5a,0x90,0xdf,0xc,0xed,
	0x97,0x15,0x1f,0xb2,0x11,0x3f,0x92,0x4b,0xa9,0xaf,0x5f,0x4e,0xb5,0x3f,0xd8,0x56,0x7b,0x44,0xf7,0x5b,
	0xae,0xe6,0xb0,0xe3,0xf9,0x24,0x57,0xe3,0xf6,0x6a,0x4d,0xe6,0xe2,0x7,0xf9,0xc4,0xe3,0x3f,0xcd,0xf,
	0x46,0x7e,0x2b,0xfa,0xa3,0x7c,0x73,0xd4,0xf4,0x7c,0xc6,0xf3,0xa8,0xac,0xe5,0x3f,0xdf,0xf,0x46,0x3e,
	0xc7,0x3f,0x7f,0xf6,0xc2,0xd9,0x9c,0x2c,0xe4,0x33,0x85,0x47,0x65,0x2d,0x7f,0xfa,0xc1,0xc8,0x2f,0xc6,
	0xa3,0x32,0x92,0x3f,0xfd,0x60,0xe4,0x2d,0xf2,0xa8,0xac,0xe5,0x4f,0x3f,0x18,0x79,0xeb,0x3c,0x2a,0x6b,
	0xf9,0xd3,0xf,0x46,0x51,0xea,0xa2,0x1f,0x8c,0xa2,0x14,0x45,0x3f,0x18,0xf9,0x11,0x3c,0x2a,0x6b,0xf9,
	0xd3,0xf,0x46,0x7e,0x4,0xef,0xfe,0xe2,0x7c,0xaa,0xfe,0x2e,0x94,0x87,0xfd,0x60,0x7e,0xd1,0x71,0xd5,
	0x12,0xd6,0xa5,0x7e,0xf,0x6a,0x11,0x26,0xd9,0xa9,0xbc,0x1e,0x54,0x35,0x78,0x72,0x17,0xf2,0x66,0x62,
	0xc1,0x80,0x5b,0x90,0x3c,0xff,0x4d,0x73,0xfe,0x58,0x13,0xe0,0x7,0xb,0x9c,0x57,0xf1,0x6,0x71,0xe7,
	0x9e,0x42,0x85,0x4b,0x17,0xff,0x55,0x80,0x55,0xfd,0x4e,0x39,0xb3,0x56,0x92,0x2f,0x4,0x2f,0xe4,0x3f,
	0xa0,0x5f,0x56,0x5c,0x8c,0xd6,0x37,0xbe,0x12,0x3f,0x6c,0xfe,0x24,0x6b,0xa6,0x92,0xf9,0x4,0x56,0x97,
	0xb2,0x3f,0x30,0xc9,0xe7,0xfc,0x63,0x7e,0x32,0x80,0x1f,0x2c,0x79,0xd5,0x9,0x8a,0x12,0xb,0x49,0x4b,
	0xd4,0x70,0xd,0x83,0xba,0x9f,0xd8,0x34,0x6b,0x35,0x8c,0x8f,0x9d,0xfc,0xe5,0xf9,0xc,0x98,0x3f,0xe5,
	0xe2,0xda,0x40,0xf2,0xc6,0xa2,0x8e,0x8f,0x37,0x14,0xd6,0xe0,0xd7,0xfd,0x60,0xb9,0x6f,0x4,0x48,0x46,
	0xf4,0x5b,0x60,0x42,0x3,0x54,0x88,0x7c,0x4,0x6b,0x56,0xc3,0x9,0x86,0x66,0xbf,0xa9,0x75,0xa2,0xaa,
	0x1,0xf3,0x27,0x57,0x5c,0x8b,0x6e,0x78,0x10,0x8b,0x8f,0x4e,0xea,0x7,0xd3,0x76,0x5e,0xb5,0x1d,0xc6,
	0x91,0xad,0x84,0x91,0xa1,0x5,0xd3,0x30,0x44,0xd6,0x86,0x14,0x35,0xef,0xc9,0xaf,0x86,0x3,0xdc,0xb7,
	0xb9,0xb7,0xf2,0xd,0xf,0x62,0xfe,0xc8,0x4,0xff,0x5,0xc0,0x8d,0x80,0x56,0x1a,0x97,0x78,0x2f,0x72,
	0x8f,0x60,0xee,0x3b,0x39,0xca,0xf1,0x85,0xc1,0xc7,0xdc,0x5e,0x1a,0xbe,0xbc,0x60,0xc5,0xfb,0xde,0x98,
	0xf9,0xe3,0xee,0x15,0xd0,0xd7,0xd,0x9,0x67,0x45,0xfc,0xaf,0xe5,0x8b,0x4b,0x75,0xc1,0x87,0x7e,0x30,
	0xf4,0xf9,0x27,0x97,0xb1,0xd0,0xaf,0x55,0xe5,0xab,0x7e,0x9b,0xe0,0x6d,0xd2,0xac,0x55,0xcd,0x7,0xea,
	0x3f,0x96,0xbc,0x50,0xcd,0xf5,0x83,0x35,0xf8,0xb5,0x94,0xfc,0x5d,0xc3,0xe6,0x8f,0x84,0xf7,0x9f,0x42,
	0x83,0x17,0x55,0x7e,0x7b,0xfd,0xa9,0xaf,0xea,0xf,0xc,0x86,0x94,0x7e,0x30,0xf2,0x52,0x3e,0x36,0xa7,
	0x35,0xc4,0x47,0xb5,0xd0,0xf8,0x94,0x79,0xfa,0xc1,0xc8,0x57,0xf8,0xd8,0x9c,0xd6,0x10,0x1f,0xd5,0x42,
	0xe3,0x53,0xe6,0xe9,0x7,0x23,0x3f,0x87,0x47,0x65,0x2d,0x7f,0xfa,0xc1,0xc8,0x1b,0xe2,0x51,0x59,0xcb,
	0x9f,0x7e,0x30,0xf2,0xd6,0x79,0x54,0xd6,0xf2,0xa7,0x1f,0x8c,0xa2,0xcc,0x89,0x7e,0x30,0x8a,0x52,0xd4,
	0xaa,0x7e,0x30,0xed,0x7c,0x18,0x7f,0xad,0xf9,0x30,0x9e,0x17,0x6a,0x55,0x3f,0x98,0x76,0x3e,0x8c,0xbf,
	0xd6,0x7c,0x18,0xcc,0xcb,0x95,0xee,0xf,0x56,0xfd,0xb6,0xfb,0xd8,0x16,0x35,0xbe,0xfa,0xbb,0x60,0x9d,
	0x12,0x5a,0xce,0x82,0x8e,0x1b,0x49,0xaf,0x57,0xbc,0x17,0x9f,0xf1,0xdf,0xde,0x7c,0xd8,0x33,0x4f,0xa8,
	0x7a,0x3d,0x29,0x3b,0x67,0x4a,0x22,0xd5,0xac,0x26,0x1e,0x72,0xa2,0x3f,0x58,0x6c,0xa9,0x4a,0x56,0x3d,
	0x57,0x8b,0xc1,0xb4,0xfd,0x48,0x65,0xc5,0x39,0xc7,0xfd,0xa0,0xe2,0x43,0x28,0x1f,0x54,0xd2,0x6c,0xe6,
	0xde,0xb6,0xe5,0x5f,0xa8,0x28,0xaf,0xfa,0xc1,0x7a,0x9d,0x29,0x8d,0xf1,0x87,0xe2,0x27,0x2f,0x13,0x5,
	0xff,0x55,0xb2,0xb2,0x76,0x58,0x7f,0x33,0x48,0xe9,0xf,0x39,0x82,0x22,0xfc,0xf8,0xe7,0xd3,0x55,0xee,
	0x30,0x26,0xcc,0xb9,0xea,0x14,0x8a,0xf7,0x92,0x33,0x9b,0xdd,0xbd,0x77,0x47,0x23,0xcf,0x6a,0xf9,0xac,
	0xfd,0x33,0x55,0xd5,0x91,0xa6,0x3c,0x7a,0xd,0x7d,0x7a,0xe9,0xbc,0x79,0xcb,0xd5,0x5d,0xdf,0xae,0x9f,
	0x40,0xdc,0x47,0xa3,0xa1,0x56,0x35,0xb7,0xc0,0x2c,0x68,0xf5,0x33,0xe5,0xeb,0x78,0x8b,0xb0,0xc1,0x6a,
	0xff,0x98,0x7e,0x40,0x4f,0xaa,0xb2,0x8e,0xef,0x3a,0xd9,0xd3,0x2d,0x38,0x67,0x92,0x7b,0x88,0xe4,0x9b,
	0x3f,0x26,0x6a,0xfa,0x99,0x92,0xa4,0xd7,0xc0,0x37,0x6f,0x38,0x52,0xe9,0x5,0x26,0x34,0xcf,0xb4,0x3d,
	0xd5,0x1c,0x57,0xb9,0xc3,0x58,0x2f,0xef,0x6a,0x72,0x2f,0xb9,0x91,0xf9,0xe9,0xc7,0x9f,0x35,0xf2,0x94,
	0x7f,0xc9,0x8c,0xcd,0x33,0x25,0xd4,0,0xbf,0xdc,0xcc,0xf,0x39,0xb6,0x5a,0xff,0xab,0xf2,0x77,0x27,
	0xf8,0x98,0xb0,0x3f,0x55,0x2c,0x94,0x8f,0x3b,0x8c,0x95,0x73,0x4e,0xc6,0xcf,0x3d,0x22,0xe6,0xf6,0x92,
	0x34,0x9b,0x95,0xed,0x61,0x68,0x9e,0xfe,0x59,0xa8,0xf6,0x43,0xeb,0x72,0xa6,0xda,0xc6,0x1f,0xd5,0x2c,
	0x7f,0x5a,0x32,0xf8,0xf1,0xf8,0x72,0xad,0xea,0x7,0xd3,0xce,0x87,0xf1,0xd7,0x9a,0xf,0x23,0x79,0x48,
	0xab,0xfa,0xc1,0xb4,0xf3,0x61,0xfc,0xb5,0xe6,0xc3,0x60,0x5e,0xae,0xd3,0xf1,0x83,0x69,0xe7,0xc3,0xf8,
	0x73,0xe3,0x5b,0xe3,0x85,0x5a,0xd5,0xf,0xa6,0x9d,0xf,0xe3,0xcf,0x8d,0x6f,0x9c,0x97,0x6b,0x61,0x3f,
	0x98,0x76,0x3e,0x8c,0x3f,0x37,0xbe,0x65,0x5e,0x2e,0xfa,0xc1,0x28,0x4a,0x51,0xff,0,0x2b,0x31,0xd3,
	0xee,0xae,0xdd,0x7c,0xf4,0,0,0,0,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82
};

TextureSet keyboard_sheet_data[] = { 
	{"29",32,64,16,16}, //z
	{"28",112,32,16,16}, //y
	{"27",48,64,16,16}, //x
	{"26",48,32,16,16}, //w
	{"25",80,64,16,16}, //v
	{"24",128,32,16,16}, //u
	{"23",96,32,16,16}, //t
	{"22",48,48,16,16}, //s
	{"21",80,32,16,16}, //r
	{"20",32,32,16,16}, //q
	{"19",176,32,16,16}, //p
	{"18",160,32,16,16}, //o
	{"17",112,64,16,16}, //n
	{"16",128,64,16,16}, //m
	{"15",160,48,16,16}, //l
	{"14",144,48,16,16}, //k
	{"13",128,48,16,16}, //j
	{"12",144,32,16,16}, //i
	{"11",112,48,16,16}, //h
	{"10",96,48,16,16}, //g
	{"9",80,48,16,16}, //f
	{"8",80,48,16,16}, //e
	{"7",64,48,16,16}, //d
	{"6",64,64,16,16}, //c
	{"5",96,64,16,16}, //b
	{"4",32,48,16,16}, //a
	{"39",16,16,16,16}, //0
	{"30",8,16,16,16}, //1
	{"31",16,16,16,16}, //2
	{"32",24,16,16,16}, //3
	{"33",32,16,16,16}, //4
	{"34",40,16,16,16}, //5
	{"35",48,16,16,16}, //6
	{"36",56,16,16,16}, //7
	{"37",64,16,16,16}, //8
	{"38",72,16,16,16}, //9
	{"44",80,80,32,16}, //[Space]
	{"33",56,16,16,16}, //!
	{"34",16,16,16,16}, //"
	{"54",8,16,16,16}, //,
	{"45",48,16,16,16}, //-
	{"55",0,16,16,16}, //.
	{"56",288,0,16,16}, // /
	{"58",0,32,16,16}, //:
	{"63",72,16,16,16}, //?
	{"82",224,64,16,16}, //UP KEY
	{"81",224,80,16,16}, //DOWN KEY
	{"79",240,80,16,16}, //RIGHT KEY
	{"80",208,80,16,16}, //LEFT KEY
	{"40",208,48,32,16}, //[enter]
	{"41",0,0,16,16}, //[esc]
	{"75",272,64,16,16}, //[SDLK_PAGEDOWN]
	{"78",272,48,16,16}, //[SDLK_PAGEUP]

    //SDL_SCANCODE_LCTRL = 224,
    //SDL_SCANCODE_LSHIFT = 225,
    //SDL_SCANCODE_LALT = 226, /**< alt, option */
    //SDL_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    //SDL_SCANCODE_RCTRL = 228,
    //SDL_SCANCODE_RSHIFT = 229,
    //SDL_SCANCODE_RALT = 230, /**< alt gr, option */
    //SDL_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */


};

