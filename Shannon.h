#pragma once
#pragma once
#include <unordered_map>
#include <algorithm>
/**
 * ������� ������������� ������������ ������������� ����.
 * @param bytes ������������������ ����, ��� ������� ����������� ������.
 * @return ������������� ������������ (������������� ������):
 * ���� - �������� �������, �������� - ����������� ��������� ���� � ������������������.
 */
std::unordered_map<char, float> estimate_proba(const std::vector<char>& bytes);
/**
 * ��������� ������� �������.
 * @param proba ������������� ������������ ������������� �������� (������������� ������):
 * ���� - �������� �������, �������� - ����������� ��������� ���� � ������������������.
 * @return ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 */
std::unordered_map<char, std::vector<bool>> build_code(const std::unordered_map<char, float>& proba);
/**
* ����������� ��������������� ������� ��� ���������� ������� �������.
* @param code - �������� ������� �������.
* @param proba - ��������������� ������ ���: <����, ����������� ���������>
* @param l - ����� �������, ������������, ������� ����� ������� �� ���, ����� ��������� ����������� ��������� � ��� ���� �������� ������
* @param r - ������ �������, �� �������� � ��� ������������
* @param path - ��� ������ � ������� ��������� � ������� ��������� �������-����
*/
void build_code(std::unordered_map<char, std::vector<bool>>& code, const std::vector<std::pair<char, float>>& proba, std::vector<float> partial, size_t l, size_t r, std::vector<bool>&& path);
/**
 * ��������� ����������� � ������� ������� �������.
 * @param bytes ����� ���� ��� �����������.
 * @param table ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 * @return ����� ���, ��������������� �������������� ������.
 */
std::vector<bool> encode(const std::vector<char>& bytes,
	const std::unordered_map<char, std::vector<bool>>& table);
/**
 * ��������� ������������� � ������� ������� �������.
 * @param bits ����� ��� ��� �������������.
 * @param table ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 * @return ����� ����, ��������������� �������������� ������.
 */
std::vector<char> decode(const std::vector<bool>& bits,
	const std::unordered_map<char, std::vector<bool>>& table);
/**
 * ������� ������������� ����������� ������ (����� ������������ ���� (8) � ������� ����� ������������).
 * @param table ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 * @param proba ������������� ������������ (������������� ������):
 * ���� - �������� �������, �������� - ����������� ��������� ���� � ������������������.
 * @return ������������� ����������� ������.
 */
float estimate_compression(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba);
/**
 * ������� ������������ ����������� ������ (�������� ���������� ���� � ���������� ���� ����� ������).
 * @param bytes_before ���������� �������� ����.
 * @param bytes_after ���������� ���� ����� ������.
 * @return ������������ ����������� ������.
 */
float estimate_compression(size_t bytes_before, size_t bytes_after);
/**
 * ��������� ������������� ����.
 * @param table ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 * @param proba ������������� ������������ (������������� ������):
 * ���� - �������� �������, �������� - ����������� ��������� ���� � ������������������.
 * @return ���� ������������� ����.
 */
bool is_optimal(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba);
/**
 * ��������� ������������ ����.
 * @param table ������� ������� (������������� ������): ���� - �������� �������, �������� - ����� ���.
 * @return ���� ������������ ����.
 */
bool is_prefix(const std::unordered_map<char, std::vector<bool>>& table);




std::pair<std::vector<bool>, std::unordered_map<char, std::vector<bool>>> ShannonCompress(std::vector<char> buffer);