
#include <vector>
#include <filesystem>
#include <string>
#include <iostream>

#include <util.h>
#include <readline/readline.h>
#include <readline/history.h>


int histo_len() {
#ifdef _MSC_VER
  return history_length();
#else
  return history_length;
#endif
}

HIST_ENTRY **get_histo(int& l) {
  l=histo_len();
  return history_list();
}

bool get_int(std::string s, int& n) {
  trim(s);

  int neg=1;

  if (s[0] == '-') {
    s=s.substr(1);
    neg=-1;
  }

  if (all_of_ctype(s, isdigit)) {
    n=neg*std::stoi(s);
    return true;
  }

  return false;
}

// Recall cmd from history by its number from the end if < 0 or from the start
std::string recall_cmd_by_num(int n) {
  int l;
  HIST_ENTRY **h=get_histo(l);
  std::string s="";

  // Rappel à partir de la fin
  if (n < 0) s=h[l+n]->line;
  // Rappel à partir du début
  else s=h[n]->line;

  return s;
}

#define trc std::cout << __LINE__ << ", SH " << sh << std::endl;
// Recall cmd from history starting from end finding string corresponding to expr
std::string recall_cmd_by_expr(std::string expr) {
  int l;
  HIST_ENTRY **h=get_histo(l);
  std::string s="";

  if (expr[0] == '?') {
    expr.erase(0,1);
    bool at_end=true;

    if (expr.back() == '?') {
      expr.pop_back();
      at_end=false;
    }

    std::string sh;
    while (--l) {
      sh=h[l]->line;

      if (at_end) {trc;
        if (sh.ends_with(expr)) return sh;
      } else {trc;
        if (sh.find(expr) != std::string::npos) return sh;
      }
    }
  } else {
    std::string sh;
    while (--l) {
      sh=h[l]->line;
      if (sh.starts_with(expr)) {
        return sh;
      }
    }
  }

  return s;
}

std::string recall_cmd_by_subst(std::string subst) {
  int l;
  HIST_ENTRY **h=get_histo(l);

  //if (subst.back() == '^') subst.pop_back();
  auto v=split(subst, '^');
  size_t p;
  std::string sh="";

  while (--l) {
    sh=h[l]->line;
    p=sh.find(v[0]);
    if (p != std::string::npos) return sh.replace(p, v[0].size(), v[1]);
  }

  return "";
}


int history_expand(char *_hs, char **_out) {
  std::string hs=_hs;
  trim(hs);
  if (hs[0] == '!')  {
    hs.erase(0, 1);
    int n;
    if (get_int(hs, n)) { // Rappel de commande numérique
      hs=recall_cmd_by_num(n);
    } else { // Rappel de commande par chaine
      // !! <=> !-1
      if (hs[0] == '!') hs=recall_cmd_by_num(-1);
      else hs=recall_cmd_by_expr(hs);
    }
  } if (hs[0] == '^')  {
    hs.erase(0, 1);
    hs=recall_cmd_by_subst(hs);
  }

  *_out=_strdup(hs.c_str());
  if (hs == "") return 1;
  return 0;
}

