#pragma once

#include <string_view>
#include <cinttypes>
#include <deque>
#include <fstream>
#include <format>

class Dot {
 public:
 using Vertex = uint64_t;
 using Edge   = uint64_t;
 
 Dot() {}
 
  Vertex AddVertex(const std::string_view& label) {
    Vertex id = verticies_.size();
    verticies_.push_back({id, label});
    return id;
  }

  Vertex AddVertexWithCopy(std::string label) {
    storage_.push_back(std::move(label));
    std::string_view str(storage_.back());
    return AddVertex(str);
  }


  Vertex AddVertex(uint64_t id, const std::string_view& label) {
    verticies_.push_back({id, label});
    return verticies_.size() - 1;
  }

  
  Vertex AddVertex(void* id, const std::string_view& label) {
    return AddVertex(std::bit_cast<uint64_t>(id), label);
  }
  
  Vertex AddVertexWithCopy(void* id, std::string label) {
    storage_.push_back(std::move(label));
    std::string_view str(storage_.back());
    return AddVertex(id, str);
  }

  Edge AddEdge(uint64_t from, uint64_t to, const std::string_view& label) {
    edges_.push_back({from, to, label});
    return edges_.size() - 1;
  }
  
  
  bool Write(const std::string_view& out_file_name) {
    std::ofstream file(out_file_name.data());
    if (file.is_open()) {
      WriteStart(file);

      for (auto& vert : verticies_) {
        file << std::format("\t{} [label=\"{}\"]\n", vert.id, vert.label);
      }

      for (auto& edge : edges_) {
        file << std::format("{} -> {} [label=\"{}\"]\n", edge.from, edge.to, edge.label);
      }

      WriteEnd(file);

      file.close();
      return true;
    }
    return false;
  }

  // void Add
 private:
  void WriteStart(std::ofstream& file) {
    file << 
    "digraph AST {\n";
  }

  void WriteEnd(std::ofstream& file) {
    file <<
    "}";
  }

  struct VertexProp {
    uint64_t id;
    std::string_view label;
  };

  struct EdgeProp {
    uint64_t from;
    uint64_t to;
    std::string_view label;
  };

  std::deque<VertexProp> verticies_;
  std::deque<EdgeProp> edges_;
  std::deque<std::string> storage_;
};