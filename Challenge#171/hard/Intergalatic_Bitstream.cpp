#include <map>
#include <queue>
#include <cctype>
#include <fstream>
#include <iostream>
#include <getopt.h>
 
struct Node {
  std::string word;
  int weight;
  Node *left, *right;
 
  bool operator<(const Node &node) const {
    return weight == node.weight ? word < node.word : weight > node.weight;
  }
 
  bool is_internal() { return word.empty(); }
};
 
struct Huffman {
  /* Initializes from sample text from a stream. */
  Huffman(const char *file) {
    std::ifstream in{file};
    std::map<std::string, int> words;
    std::string word;
    /* Parse each individual word. */
    while (!in.eof()) {
      int c = in.get();
      if (std::isalnum(c)) {
        word.push_back(std::toupper(c));
      } else if (word.size() > 0) {
        words[word]++;
        word.clear();
      }
    }
    /* Build Huffman tree. */
    std::priority_queue<Node> queue;
    for (auto &kv : words) {
      queue.push(Node{kv.first, kv.second, nullptr, nullptr});
    }
    while (queue.size() > 1) {
      Node *left = new Node(queue.top());
      queue.pop();
      Node *right = new Node(queue.top());
      queue.pop();
      queue.push(Node{"", left->weight + right->weight, left, right});
    }
    root = new Node(queue.top());
    std::vector<bool> empty;
    fill(root, empty);
  }
 
  /* Fill out the lookup table. */
  void fill(Node *root, std::vector<bool> &bits) {
    if (root->is_internal()) {
      bits.push_back(false);
      fill(root->left, bits);
      bits.pop_back();
      bits.push_back(true);
      fill(root->right, bits);
      bits.pop_back();
    } else {
      lookup[root->word] = bits;
    }
  }
 
  /* Add word to output. */
  void add(std::string word) {
    auto &encoding = lookup[word];
    if (encoding.empty()) {
      std::cerr << "Unknown word: " << word << std::endl;
      exit(1);
    } else {
      for (const auto &b : encoding) bits.push_back(b);
    }
  }
 
  void decompress(std::istream &in, std::ostream &out) {
    uint8_t c = in.get();
    int tail = c >> 5 == 0 ? 8 : c >> 5;
    c <<= 3;
    int count = 5;
    Node *node = root;
    while (true) {
      while (count > 0) {
        if (node->is_internal()) {
          node = c & 0x80 ? node->right : node->left;
          c <<= 1;
          count--;
        } else {
          out << node->word << " ";
          node = root;
        }
      }
      if (in.eof()) break;
      c = in.get();
      in.peek();  // peek for EOF
      count = in.eof() ? tail : 8;
    }
    if (!node->is_internal()) out << node->word << " ";
  }
 
  std::map<std::string, std::vector<bool>> lookup;
  std::vector<bool> bits;
  Node *root;
};
 
/* Write encoding to output. */
std::ostream &operator<<(std::ostream &out, const Huffman &encoder) {
  uint8_t fill = (encoder.bits.size() + 3) % 8;
  int count = 3;
  for (const auto &b : encoder.bits) {
    if (count == 8) {
      out.write((char *)&fill, 1);
      count = 0;
    }
    fill <<= 1;
    fill |= b;
    count++;
  }
  fill <<= 8 - count;
  out.write((char *)&fill, 1);
  return out;
}
 
int main(int argc, char **argv) {
  const char *dict = "/dev/null";
  bool compress = true;
  int c;
  while ((c = getopt(argc, argv, "cdf:")) != -1) {
    switch (c) {
      case 'c':
        compress = true;
        break;
      case 'd':
        compress = false;
        break;
      case 'f':
        dict = optarg;
        break;
    }
  }
 
  Huffman encoder{dict};
  if (compress) {
    std::string word;
    while (std::cin >> word) {
      encoder.add(word);
    }
    std::cout << encoder;
  } else {
    encoder.decompress(std::cin, std::cout);
    std::cout << std::endl;
  }
  return 0;
}