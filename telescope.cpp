#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

// Read m_size.first * m_size.second characters from istream in.
// Store characters in vector.
// Exception is thrown if there are not enough data
std::vector<unsigned char> parse_stream(std::istream& in, const std::pair<size_t, size_t>& m_size)
{
	size_t v_size = m_size.first * m_size.second;
	std::vector<unsigned char> m_vector;
	char c;
	
	for (size_t i = 0; i < v_size; i++) {
		in.get(c);
		if (in.eof()) {
			// Input stream had not enough elements. It is inconsistent number of elements
			throw std::invalid_argument("End of input stream."); // Programm aborts here
		}
		m_vector.push_back(c);
	}
	
	return m_vector;
}

void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step);

// Scroll down matrix rows by 1.
void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec)
{
	rotate_down(m_size, vec, 1);
}

// If step > 0 scroll down rows by step.
// If step < 0 scroll up rows by step
// If step = 0 no scroll done.
void rotate_down(const std::pair<size_t, size_t>& m_size, std::vector<unsigned char>& vec, int step)
{
	if (step < 0) {
		step = -step;
		step = step % m_size.first;
		std::rotate(vec.begin(), vec.begin() + m_size.second * step, vec.end());
	} else {
		step = step % m_size.first;
		std::rotate(vec.begin(), vec.begin() + m_size.second * (m_size.first - step), vec.end());
	}
}

void print_vector(const std::pair<size_t, size_t>& m_size, const std::vector<unsigned char>& vec)
{
	for (size_t i = 0; i < m_size.first; i++) {
		for (size_t j = 0; j < m_size.second; j++) {
			std::cout << "'"  << vec.at(i * m_size.second + j) << "' ";
		}
		std::cout << "\n";
	}
}

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " step\n";
		return 1;
	}
	int step = atoi(argv[1]);
	std::pair<size_t, size_t> in_size(3, 2);
	std::vector<unsigned char> tmp = parse_stream(std::cin, in_size);

	print_vector(in_size, tmp);

	rotate_down(in_size, tmp, step);
	std::cout << "Resulting matrix with step : " << step << "\n";
	print_vector(in_size, tmp);
	
	return 0;
}
