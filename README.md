### How to test?

- Install yasm:

```sudo apt-get install yasm```

Clone repo:

	git clone https://github.com/DeckerSU/sha256_tests
	cd sha256_tests
	
- Start test:

```make -j$(nproc) && bin/Release/test```

Get results like this:

	Hardware SHA256 [type]: AVX
	Hardware SHA256:
	bb7aa507ee307613a18d2b1eabb42e76a5e3ff8a00d021b738f6a5a8f299ed29
	Total time = 2.433698 seconds
	Software SHA256:
	bb7aa507ee307613a18d2b1eabb42e76a5e3ff8a00d021b738f6a5a8f299ed29
	Total time = 3.395078 seconds
	bb7aa507ee307613a18d2b1eabb42e76a5e3ff8a00d021b738f6a5a8f299ed29
	
- Change `#define SHA_TYPE 1` in `cryptoext/sha256.h` to next value (mean from 1 to 2), repeat test.
- Make same test for all 1..4 values to find which is best for your CPU(s).
