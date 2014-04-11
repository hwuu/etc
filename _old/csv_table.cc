// $Id: csv_table.cc 5444 2012-03-11 11:41:41Z haowu $

#include "csv_table.h"

CsvTable::CsvTable(const string& csv_file)
{
  FILE *f = fopen(csv_file.c_str(), "r");
  fseek(f, 0, SEEK_END);
  long l = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *buf = (char *)malloc(l + 1);
  fread(buf, l, 1, f);
  fclose(f);
  buf[l] = 0;
  z_buff_.push_back(buf);
  char *rp = buf;
  while (*rp) {
    if (*rp == '\"') {
      rp++;
      z_attr_name_.push_back(rp);
      char *wp = rp;
      do {
        while (*rp && *rp != '\"')
          *wp++ = *rp++;
        if (*rp)rp++;
        if (*rp == '\"')
          *wp++ = *rp++;
        else break;
      } while(1);
      *wp = 0;
    } else {
      z_attr_name_.push_back(rp);
      while (*rp && *rp != ',' && *rp != '\r' && *rp != '\n')
        rp++;
    }
    if (*rp == '\r')
      *rp++ = 0;            
    if (*rp == '\n') {
      *rp++ = 0;
      break;
    }
    if (*rp == 0)
      break;
    if (*rp == ',')
      *rp++ = 0;
  }
  while (*rp) {
    data_.resize(data_.size() + 1);
    while (*rp) {
      if (*rp == '\"') {
        rp++;
        if (data_.back().size() < z_attr_name_.size())
          data_.back().push_back(rp);
        char* wp = rp;
        while (true) {
          while (true) {
            if (*rp == 0 || *rp == '\"') {
              break;
            } else if (*rp == '\\') {
              *wp = *rp;
              wp += 2;
              rp += 2;
            } else {
              *wp = *rp;
              wp += 1;
              rp += 1;
            }
          }
          if (*rp)
            rp++;
          if (*rp == '\"') {
            *wp++ = *rp++;
          } else {
            break;
          }
        }
        *wp = 0;
      } else {
        if (data_.back().size() < z_attr_name_.size())
          data_.back().push_back(rp);
        while (*rp && *rp != ',' && *rp != '\r' && *rp != '\n')
          rp++;
      }
      if (*rp == '\r')
        *rp++ = 0;
      if (*rp == '\n') {
        *rp++ = 0;
        break;
      }
      if (*rp == 0)
        break;
      if (*rp == ',')
        *rp++ = 0;
    }
    while (data_.back().size() < z_attr_name_.size())
      data_.back().push_back(buf + l);
  }
}

CsvTable::~CsvTable()
{
  Clear();
}

void CsvTable::AddFile(const string& csv_file, bool skipFirstLine)
{
  FILE *f = fopen(csv_file.c_str(), "r");
  fseek(f, 0, SEEK_END);
  long l = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *buf = (char *)malloc(l + 1);
  fread(buf, l, 1, f);
  fclose(f);
  buf[l] = 0;
  z_buff_.push_back(buf);

  char *rp = buf;
  while (*rp) {
    if (!skipFirstLine)
      data_.resize(data_.size() + 1);
    while (*rp) {
      if (*rp == '\"') {
        rp++;
        if (!skipFirstLine && data_.back().size() < z_attr_name_.size())
          data_.back().push_back(rp);
        char *wp = rp;
        do {
          while (*rp && *rp != '\"')
            *wp++ = *rp++;
          if (*rp)
            rp++;

          if (*rp == '\"')
            *wp++ = *rp++;
          else break;
        } while (1);
        *wp = 0;
      } else {
        if (!skipFirstLine && data_.back().size() < z_attr_name_.size())
          data_.back().push_back(rp);
        while (*rp && *rp != ',' && *rp != '\r' && *rp != '\n')
          rp++;
      }
      if (*rp == '\r')
        *rp++ = 0;
      if (*rp == '\n') {
        *rp++ = 0;
        break;
      }
      if (*rp == 0)
        break;
      if (*rp == ',')
        *rp++ = 0;
    }
    while (!skipFirstLine && data_.back().size() < z_attr_name_.size())
      data_.back().push_back(buf + l);
    skipFirstLine = false;
  }
}

void CsvTable::Clear()
{
  data_.clear();
  for (int i = 0; i < (int)z_buff_.size(); i++)
    free(z_buff_[i]);
}

int CsvTable::GetSizeInByte()
{
  int n = 0;
  for (int tid = 0; tid < (int)data_.size(); tid++) {
    for (int i = 0; i < (int)data_[tid].size(); i++) {
      string str = string(data_[tid][i]);
      n += str.length() * sizeof(char) + sizeof(const char*);
    }
    n += sizeof(vector<string>);
  }
  return n;
}