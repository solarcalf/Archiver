#include "Shannon.h"

std::unordered_map<char, float> estimate_proba(const std::vector<char>& bytes) {
	std::unordered_map<char, size_t> amount_of_byte;	// also we can use array with array.size() = 256			 //
	std::unordered_map<char, float> proba;				// it will perform better because in this case we don't make //  
	size_t amount_of_bytes = bytes.size();				// any request for dynamic memory							 //
														// but we will iterate through all array then   			 //
	for (const auto& byte : bytes)
		amount_of_byte[byte]++;

	for (const auto& [byte, amount] : amount_of_byte)
		proba[byte] = static_cast<float>(amount) / amount_of_bytes;

	return proba;
}

std::unordered_map<char, std::vector<bool>> build_code(const std::unordered_map<char, float>& proba) {
	std::unordered_map<char, std::vector<bool>> code;
	std::vector<std::pair<char, float>> sorted_proba;

	for (const auto& [key, value] : proba)
		sorted_proba.emplace_back(key, value);

	size_t SIZE = sorted_proba.size();
	bool need_sort = true;

	// Check if it is correct
	std::sort(std::begin(sorted_proba), std::end(sorted_proba), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});

	std::vector<float> partial_sum_proba;
	partial_sum_proba.resize(proba.size() + 1);
	partial_sum_proba[0] = 0;

	for (size_t i = 0; i < proba.size(); i++)
		partial_sum_proba[i + 1] = partial_sum_proba[i] + sorted_proba[i].second;

	build_code(code, sorted_proba, partial_sum_proba, 0, SIZE, std::vector<bool>());

	return code;
}


void build_code(std::unordered_map<char, std::vector<bool>>& code,
	const std::vector<std::pair<char, float>>& proba, const std::vector<float> partial_sum_proba,
	size_t l, size_t r, std::vector<bool>&& path) {

	if (l + 1 >= r) {
		code[proba[l].first] = std::move(path);
		return;
	}

	/*
	float summary_proba = 0;

	for (size_t i = l; i < r; i++) ///////////////////// USE PARTIAL SUMS HERE INSTEAD - DONE
		summary_proba += proba[i].second; */


		// Well now it performs faster but it's a lotta garbage in here 
		// hard to read and understand
		// will it be better to create static var of our structure
		// which will do all staff with making partial sums in constructor?
		// in this case we will now give one more arg to recursive build_cod
	float summary_proba = partial_sum_proba[r] - partial_sum_proba[l];


	float left_summary_proba = proba[l].second;
	size_t lp = l;

	while (lp + 1 < r && left_summary_proba < summary_proba - (left_summary_proba + proba[lp + 1].second)) {
		lp++;
		left_summary_proba += proba[lp].second;
	}

	lp++; // lp pointed to the very right element of left subset

	std::vector<bool> right_branch_path = std::move(path);
	std::vector<bool> left_branch_path = right_branch_path;

	right_branch_path.push_back(1);
	left_branch_path.push_back(0);

	build_code(code, proba, partial_sum_proba, l, lp, std::move(left_branch_path));
	build_code(code, proba, partial_sum_proba, lp, r, std::move(right_branch_path));
}

std::vector<bool> encode(const std::vector<char>& bytes, const std::unordered_map<char, std::vector<bool>>& table) {
	std::vector<bool> encoded_sequence;

	for (const auto& byte : bytes) {
		auto it = table.find(byte);
		for (const auto& x : (*it).second)
			encoded_sequence.push_back(x);	// is it possible to emplace_back code vector(it->second) instead of loop? 
	}										// answer: no, but there is new feature in C++23 for this occasion

	return encoded_sequence;
}

std::vector<char> decode(const std::vector<bool>& bits,
	const std::unordered_map<char, std::vector<bool>>& table) {
	std::vector<char> decoded_sequence;
	std::unordered_map<std::vector<bool>, char> reversed_table;

	for (const auto& [byte, code] : table)
		reversed_table[code] = byte;

	std::vector<bool> current_code;

	for (const auto bit : bits) {
		current_code.push_back(bit);

		auto it = reversed_table.find(current_code);
		if (it != reversed_table.end()) {
			decoded_sequence.push_back((*it).second);
			current_code.clear();
		}
	}

	return decoded_sequence;
}

float estimate_compression(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba) {
	float l_avg = 0;
	float l_ravn = ceil(log2(table.size()));

	for (const auto& [byte, code] : table)
		l_avg += table.at(byte).size() * proba.at(byte);

	return l_ravn / l_avg;
}

float estimate_compression(size_t bytes_before, size_t bytes_after) {
	return static_cast<float>(bytes_before) / bytes_after;
}

bool is_optimal(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba) {
	float H = 0;
	float l_avg = 0, l_opt = 0;

	for (const auto& [byte, code] : table) {
		float prob = proba.at(byte);
		H -= prob * log2(prob);
		l_avg += table.at(byte).size() * prob;
	}

	l_opt = H / (log2(table.size()));

	return (l_opt <= l_avg && l_avg <= l_avg + 1);
}

bool is_prefix(const std::unordered_map<char, std::vector<bool>>& table) {
	auto pre_end = table.end();
	pre_end--;


	for (auto it1 = table.begin(); it1 != pre_end; it1++)
		for (auto it2 = it1; it2 != pre_end;) {
			it2++;

			bool prefix_flag = true;

			const std::vector<bool>& code1 = (*it1).second;
			const std::vector<bool>& code2 = (*it2).second;

			size_t min_SIZE = std::min(code1.size(), code2.size());

			for (size_t i = 0; i < min_SIZE; i++)
				if (code1[i] != code2[i]) {
					prefix_flag = false;
					break;
				}

			if (prefix_flag == true)
				return false;
		}

	return true;
}

std::pair<std::vector<bool>, std::unordered_map<char, std::vector<bool>>> ShannonCompress(std::vector<char> buffer) {
	std::unordered_map<char, float> proba = estimate_proba(buffer);	
	std::unordered_map<char, std::vector<bool>> table = build_code(proba);
	std::vector<bool> code = encode(buffer, table);

	return {code, table};
}