#include "Shannon.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <string>

using namespace std;
using vi = vector<int>;


#define ARCHIEVE

#ifdef ARCHIEVE

int main() {

	//------------------------------------------------READ---------------------------------------------//
	auto _begin = std::chrono::steady_clock::now();

	string path = "D:\\Programming\\C++\\Archiver\\allchars.txt";
	std::ifstream file(path, std::ios::binary);

	// Get the size of the file
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	
	// Create a vector to store the byte sequence
	std::vector<char> buffer(fileSize);				
	
	// Read the file into the vector
	file.read(buffer.data(), fileSize);
	
	// Close the file
	file.close();

	auto _end = std::chrono::steady_clock::now();
	auto _elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _begin);
	std::cout << "The time: " << _elapsed_ms.count() << " ms\n";

	//---------------------------------------------BUILD_CODE------------------------------------------//
	auto begin = std::chrono::steady_clock::now();

	//cout << "Message to code:\n";
	//for (auto x : buffer)
	//	cout << x << ' ';
	//cout << "\n\n";
	
	auto [code, table] = ShannonCompress(buffer);
	
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";


	cout << "msg:\t" << buffer.size() << "\ncode:\t" << code.size() / 8 << "\n\n\n" 
		<< "table.size(): " << table.size();



	//cout << "encoded msg: ";
	//for (auto x : code)
	//	cout << x;
	
	cout << "\ntable for encoding:\n";
	for (auto [key, val] : table) {
		cout << key << ' ';
		for (auto x : val)
			cout << x;
		cout << '\n';
	}

	//-----------------------------------------------WRITE---------------------------------------------//
	
	std::ofstream outFile("compressed.bin", std::ios::binary);
	int numBits = code.size();
	int numBytes = (numBits + 7) / 8; // round up to nearest byte
	for (int i = 0; i < numBytes; i++) {
		char byte = 0;
		for (int j = 0; j < 8; j++) {
			int bitIndex = i * 8 + j;
			if (bitIndex < numBits) {
				if (code[bitIndex]) {
					byte |= (1 << j);
				}
			}
		}
		outFile.write(&byte, sizeof(byte));
	}
	outFile.close();


	//-----------------------------------------------DECODE-------------------------------------------//
	
	
}

#endif


// Ryan.jpg : 53 56 56


#ifndef ARCHIEVE


int main() {
		

}


#endif