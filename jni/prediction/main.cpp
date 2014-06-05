/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ConvertUTF.h"
#include <stdio.h>
#include <string.h>
#include "../include/matrixsearch.h"

using namespace ime_pinyin;

static MatrixSearch* g_pMatrixSearch = NULL;

static const char*
toUTF8(const char16* src, size_t length) {
  static UTF8 g_utf8_buf[100] = { 0 };
  UTF16 *utf16Start = (UTF16 *) src;
  UTF16 *utf16End = (UTF16 *) (src + length);
  UTF8* utf8Start = g_utf8_buf;
  ConvertUTF16toUTF8((const UTF16 **) &utf16Start, utf16End, &utf8Start,
      &(g_utf8_buf[100]), strictConversion);
  return (const char*) g_utf8_buf;
}

static const char16*
toUTF16(const char* src) {
  static UTF16 g_uf16_buf[100] = { 0 };
  const UTF8* utf8Start = (const UTF8 *)src;
  const UTF8* utf8End = (const UTF8 *)(src + strlen(src));
  UTF16* utf16Start = g_uf16_buf;
  ConvertUTF8toUTF16(&utf8Start, utf8End, &utf16Start, &g_uf16_buf[100], strictConversion);
  return (const char16*)g_uf16_buf;
}

extern "C" {

bool
InitPrediction(const char* dict_file)
{
  g_pMatrixSearch = new MatrixSearch();
  return g_pMatrixSearch->init(dict_file, "dummy_user_dict");
}

// Prediction phrase are separated by spaces.
const char* GetPrediction(const char* str)
{
  static const int MAX_PHRASE_COUNT = 50;
  static char16 predictBuffer[MAX_PHRASE_COUNT][kMaxPredictSize + 1];
  // A utf8 Chinese character takes two or three chars and each phrase takes
  // at most kMaxPredictSize * 3 chars. We insert a space char, which takes one
  // char, between two phrases and add '\0' to the end of the last phrase. So
  // MAX_PHRASE_COUNT extra chars will be added.
  static char resultBuffer[MAX_PHRASE_COUNT * (kMaxPredictSize * 3 + 1)];

  const char16* w = toUTF16(str);
  size_t n = g_pMatrixSearch->get_predicts(w, predictBuffer, MAX_PHRASE_COUNT);

  resultBuffer[0] = '\0';
  for (size_t i = 0; i < n; i++) {
    strncat(resultBuffer,
            toUTF8(predictBuffer[i], kMaxPredictSize + 1),
            kMaxPredictSize * 3);
    if (i != n - 1) {
      strncat(resultBuffer, " ", 1);
    }
  }
  return resultBuffer;
}

void
ExitPrediction()
{
  if (!g_pMatrixSearch) {
    return;
  }
  g_pMatrixSearch->close();
  delete g_pMatrixSearch;
}

int
main(int argc, char* argv[]) {
  char word[256] = "我们";
  if (argc > 1) {
    strncpy(word, argv[1], 256);
  }
  char fileName[] = "dict_pinyin.png";
  if (!InitPrediction(fileName)) {
    printf("Failed to open dict file %s\n", fileName);
    return -1;
  }
  printf("Prediction word(s) for %s:\n %s\n", word, GetPrediction(word));
  ExitPrediction();
  return 0;
}
} // extern "C" {
