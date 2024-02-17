#pragma once
#pragma once
#include <unordered_map>
#include <algorithm>
/**
 * Оценить распределение вероятностей встречаемости байт.
 * @param bytes последовательность байт, для которой выполняется оценка.
 * @return распределение вероятностей (ассоциативный массив):
 * ключ - значение символа, значение - вероятность встретить байт в последовательности.
 */
std::unordered_map<char, float> estimate_proba(const std::vector<char>& bytes);
/**
 * Построить кодовую таблицу.
 * @param proba распределение вероятностей встречаемости символов (ассоциативный массив):
 * ключ - значение символа, значение - вероятность встретить байт в последовательности.
 * @return кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 */
std::unordered_map<char, std::vector<bool>> build_code(const std::unordered_map<char, float>& proba);
/**
* Рекурсивная вспомогательная функция для построения кодовой таблицы.
* @param code - итоговая кодовая таблица.
* @param proba - отсортированный вектор пар: <байт, вероятность встретить>
* @param l - левая граница, подмножества, которое нужно разбить на два, чтобы суммарная вероятность элементов в них была примерно равной
* @param r - первый элемент, не входящий в это подмножество
* @param path - как попали в текущее поддерево с помощью алгоритма Шеннона-Фано
*/
void build_code(std::unordered_map<char, std::vector<bool>>& code, const std::vector<std::pair<char, float>>& proba, std::vector<float> partial, size_t l, size_t r, std::vector<bool>&& path);
/**
 * Выполнить кодирование с помощью кодовой таблицы.
 * @param bytes набор байт для кодирования.
 * @param table кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 * @return набор бит, соответствующих закодированным данным.
 */
std::vector<bool> encode(const std::vector<char>& bytes,
	const std::unordered_map<char, std::vector<bool>>& table);
/**
 * Выполнить декодирование с помощью кодовой таблицы.
 * @param bits набор бит для декодирования.
 * @param table кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 * @return набор байт, соответствующих декодированным данным.
 */
std::vector<char> decode(const std::vector<bool>& bits,
	const std::unordered_map<char, std::vector<bool>>& table);
/**
 * Оценить теоретический коэффициент сжатия (длина равномерного кода (8) к средней длине оптимального).
 * @param table кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 * @param proba распределение вероятностей (ассоциативный массив):
 * ключ - значение символа, значение - вероятность встретить байт в последовательности.
 * @return теоретический коэффициент сжатия.
 */
float estimate_compression(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba);
/**
 * Оценить практический коэффициент сжатия (исходное количество байт к количеству байт после сжатия).
 * @param bytes_before количество исходных байт.
 * @param bytes_after количество байт после сжатия.
 * @return практический коэффициент сжатия.
 */
float estimate_compression(size_t bytes_before, size_t bytes_after);
/**
 * Проверить оптимальность кода.
 * @param table кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 * @param proba распределение вероятностей (ассоциативный массив):
 * ключ - значение символа, значение - вероятность встретить байт в последовательности.
 * @return флаг оптимальности кода.
 */
bool is_optimal(const std::unordered_map<char, std::vector<bool>>& table,
	const std::unordered_map<char, float>& proba);
/**
 * Проверить префиксность кода.
 * @param table кодовая таблица (ассоциативный массив): ключ - значение символа, значение - набор бит.
 * @return флаг префиксности кода.
 */
bool is_prefix(const std::unordered_map<char, std::vector<bool>>& table);




std::pair<std::vector<bool>, std::unordered_map<char, std::vector<bool>>> ShannonCompress(std::vector<char> buffer);