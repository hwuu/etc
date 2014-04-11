// $Id: trie.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_TEXT_TRIE_H_
#define _ETC_TEXT_TRIE_H_

#include <string>
#include <vector>

using namespace std;

//
//
//

struct BaseTrieNode
{
  BaseTrieNode()
    : c_(0), p_parent_(NULL), p_prev_sibling_(NULL), p_next_sibling_(NULL), p_first_child_(
    NULL), p_last_child_(NULL)
  {
  }
  //
  char c_;
  BaseTrieNode* p_parent_;
  BaseTrieNode* p_prev_sibling_;
  BaseTrieNode* p_next_sibling_;
  BaseTrieNode* p_first_child_;
  BaseTrieNode* p_last_child_;
};

//
//
//

void BaseTrie_Init(BaseTrieNode** pp_bt_root);
void BaseTrie_Add(const char* str, BaseTrieNode* p_bt_root);
void BaseTrie_Find(const char* str, const BaseTrieNode& bt_root,
    BaseTrieNode** pp_result);
void BaseTrie_Destroy(BaseTrieNode* p_bt_root);

//
//
//

struct RadixTrieNode
{
  struct Compare
  {
    bool operator ()(RadixTrieNode* p1, RadixTrieNode* p2)
    {
      return (p1->str_.c_str())[0] < (p2->str_.c_str())[0];
    }
  };
  //
  RadixTrieNode()
      : id_(-1), str_(""), p_parent_(NULL), data_(NULL)
  {
  }
  //
  int id_;
  string str_;
  vector<char> z_c_;
  RadixTrieNode* p_parent_;
  vector<RadixTrieNode*> zp_child_;
  void* data_;
};

//
//
//

void RadixTrie_Init(const BaseTrieNode& bt_root, RadixTrieNode** pp_rt_root);
void RadixTrie_Find(const char* str, const RadixTrieNode& rt_root,
    RadixTrieNode** pp_result);
void RadixTrie_Destroy(RadixTrieNode* p_rt_root);
int  RadixTrie_GetSizeInByte(const RadixTrieNode& rt_root);
//
void _RadixTrie_AssignNodeIds(RadixTrieNode* p_rt_root);
void _RadixTrie_AssignNodeIds(RadixTrieNode* p_rt_root, int* p_begin);

//
//
//

/*
 * It is recommended to use this Trie class instead of above C-style functions
 */
class Trie
{
public:
  Trie();
  ~Trie();
  void Build(const vector<string>& z_str, char eos);
  void FindNodeByPrefix(const string& prefix, RadixTrieNode** pp_result) const;
  void FindNodeById(int id, RadixTrieNode** pp_result) const;
  void GetLeafNodes(vector<RadixTrieNode*>* pzp_leaf_node) const;
  void GetLeafNodes(RadixTrieNode* p_root, vector<RadixTrieNode*>* pzp_leaf_node) const;
  string GetString(RadixTrieNode* p_node) const;
  //pair<int, int> GetNodeIdInterval(int node_id) const;
  int GetNumberOfLeafNodes() const;
  int GetNumberOfNodes() const;
  int GetSizeInByte() const;
  RadixTrieNode* GetRoot() const;
protected:
  void _CountNodes();
  void _CountNodes(RadixTrieNode* p_root);
  void _BuildNodeIndex();
  void _BuildNodeIndex(RadixTrieNode* p_root);
  //void CalculateNodeIdIntervals(RadixTrieNode* p_node);
  //
  RadixTrieNode* p_root_;
  vector<RadixTrieNode*> zp_node_;
  //vector<pair<int, int> > z_interval_; // intervals, indexed by node ids
  int n_leaf_node_;
  int n_node_;
};

//
//
//

#endif
