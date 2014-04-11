#include "raw_query.h"

RawQuery::RawQuery(const char* query_string)
{
  const int L = strlen(query_string);
  buff_ = (char*)malloc(2 * L + 2);
  strcpy(buff_, query_string);
  size_ = L + 1;
  //
  char *p = buff_;
  while(*p) {
    if(*p == '+')*p = ' ';
    p++;
  }
  //
  p = buff_;
  while (*p) {
    char *p1 = p;
    while (*p && *p != '=') {
      p++;
    }
    if (*p) {
      char *p2 = p;
      while (*p && *p != '&') {
        p++;
      }
      string key(p1, p2 - p1);
      params_[key] = buff_ + size_;
      if (p - p2 - 1) {
        _DecodeURI(p2 + 1, p - p2 - 1, buff_ + size_);
      } else {
        buff_[size_] = 0;
      }
      size_ += (strlen(buff_ + size_) + 1);
      if (*p) {
        p++;
      }
    }
  }
}

RawQuery::~RawQuery(void)
{
  free(buff_);
}

const char* RawQuery::Get(const string& key) const
{
  if (key == "") {
    return buff_;
  }
  map<string, const char*>::const_iterator cit;
  cit = params_.find(key);
  if (cit == params_.end()) {
    return NULL;
  }
  return cit->second;
}

//

char* RawQuery::_DecodeURI(const char* str, int len, char* target)
{
  char *ret, *out;
  const char *in;

  if (str == NULL)
    return(NULL);
  if (len <= 0) len = strlen(str);
  if (len < 0) return(NULL);

  if (target == NULL) {
    ret = (char *) malloc(len + 1);
    if (ret == NULL) {
      //printf("xmlURIUnescapeString: out of memory\n");
      return(NULL);
    }
  } else
    ret = target;
  in = str;
  out = ret;
  while(len > 0) {
    if ((len > 2) && (*in == '%') && (_IsHex(in[1])) && (_IsHex(in[2]))) {
      in++;
      if ((*in >= '0') && (*in <= '9'))
        *out = (*in - '0');
      else if ((*in >= 'a') && (*in <= 'f'))
        *out = (*in - 'a') + 10;
      else if ((*in >= 'A') && (*in <= 'F'))
        *out = (*in - 'A') + 10;
      in++;
      if ((*in >= '0') && (*in <= '9'))
        *out = *out * 16 + (*in - '0');
      else if ((*in >= 'a') && (*in <= 'f'))
        *out = *out * 16 + (*in - 'a') + 10;
      else if ((*in >= 'A') && (*in <= 'F'))
        *out = *out * 16 + (*in - 'A') + 10;
      in++;
      len -= 3;
      out++;
    } else {
      *out++ = *in++;
      len--;
    }
  }
  *out = 0;
  return ret;
}

int RawQuery::_IsHex(char c)
{
  return (
           ((c >= '0') && (c <= '9')) ||
           ((c >= 'a') && (c <= 'f')) ||
           ((c >= 'A') && (c <= 'F'))
         );
}
