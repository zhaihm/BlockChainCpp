#include "Util.h"
#include "cryptopp\sha.h"
#include "cryptopp\hex.h"
#include <ctime>
#include <sstream>

std::string Util::GetTimestamp()
{
    time_t t;
    time(&t);
    
	std::stringstream ss;
	ss << t;
	return ss.str();
}

std::string Util::Hex2Bin(const std::string& hex)
{
	int len = hex.length();
	std::string newString;
	for (int i = 0; i < len; i += 2)
	{
		std::string byte = hex.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
		newString.push_back(chr);
	}

	return newString;
}

std::string Util::RepeatString(std::string str, std::size_t n)
{
	// https://codereview.stackexchange.com/questions/114295/repeating-a-stdstring-n-times
	if (n == 0) {
		return std::string();
	}

	if (n == 1 || str.empty()) return str;

	const auto repeat_size = str.size();

	if (repeat_size == 1) {
		str.append(n - 1, str.front());
		return str;
	}

	str.reserve(repeat_size * n);

	const auto m = static_cast<decltype(n)>(std::floor(std::log2(n)));

	for (auto i = m; i > 0; --i) str += str;

	n -= static_cast<decltype(n)>(std::pow(2, m));

	str.append(std::cbegin(str), std::next(std::cbegin(str), n * repeat_size));

	return str;
}

std::string Util::SHA256(const std::string & str)
{
	CryptoPP::SHA256 hash;
	char digest[CryptoPP::SHA256::DIGESTSIZE];

	hash.CalculateDigest(reinterpret_cast<CryptoPP::byte *>(digest),
		reinterpret_cast<const CryptoPP::byte *>(str.c_str()), 
		str.length());

	CryptoPP::HexEncoder encoder;
	std::string output;

	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(reinterpret_cast<CryptoPP::byte *>(digest), sizeof(digest));
	encoder.MessageEnd();

	return output;
}
