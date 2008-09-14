/******************************************************************************
 *
 * 
 *
 * Copyright (C) 1997-2008 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby 
 * granted. No representations are made about the suitability of this software 
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#include <stdlib.h>

#include "qtbc.h"
#include <qdir.h>
#include "message.h"
#include "htmlgen.h"
#include "config.h"
#include "util.h"
#include "doxygen.h"
#include "logos.h"
#include "diagram.h"
#include "version.h"
#include "dot.h"
#include "language.h"
#include "htmlhelp.h"
#include "docparser.h"
#include "htmldocvisitor.h"
#include "index.h"
#include "pagedef.h"
#include "debug.h"
#include "dirdef.h"
#include "vhdldocgen.h"
#include "layout.h"

// #define GROUP_COLOR "#ff8080"

//#define DBG_HTML(x) x;
#define DBG_HTML(x) 

static const char defaultStyleSheet[] = 
#include "doxygen_css.h"
;

static const char search_script[]=
#include "search_php.h"
;

static QCString g_header;
static QCString g_footer;

//------------------------- Pictures for the Tabs ------------------------

static unsigned char tab_b_gif[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x01, 0x00, 0x01, 0x00, 0x80, 0x00,
  0x00, 0x84, 0xb0, 0xc7, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x01, 0x00, 0x00, 0x02, 0x02, 0x44, 0x01, 0x00, 0x3b
};
static unsigned int tab_b_gif_len = 35;

static unsigned char tab_l_gif[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x09, 0x00, 0x2c, 0x01, 0xd5, 0x00,
  0x00, 0xf6, 0xf7, 0xf9, 0xf1, 0xf4, 0xf7, 0xf6, 0xf8, 0xfa, 0xfc, 0xfd,
  0xfe, 0xfa, 0xfb, 0xfc, 0xf9, 0xfa, 0xfb, 0xf8, 0xf9, 0xfa, 0xea, 0xef,
  0xf3, 0xef, 0xf3, 0xf6, 0xc6, 0xd5, 0xdf, 0xd2, 0xde, 0xe6, 0xd8, 0xe2,
  0xe9, 0xde, 0xe7, 0xed, 0xdd, 0xe6, 0xec, 0xe5, 0xec, 0xf1, 0xe8, 0xee,
  0xf2, 0xf4, 0xf7, 0xf9, 0xf3, 0xf6, 0xf8, 0xb3, 0xc8, 0xd5, 0xc1, 0xd2,
  0xdd, 0xcb, 0xd9, 0xe2, 0xcf, 0xdc, 0xe4, 0xd6, 0xe1, 0xe8, 0x96, 0xb4,
  0xc5, 0x9d, 0xb9, 0xc9, 0xaf, 0xc2, 0xcd, 0xbb, 0xce, 0xd9, 0xc3, 0xd4,
  0xde, 0xc2, 0xd3, 0xdd, 0xc8, 0xd7, 0xe0, 0xcc, 0xda, 0xe2, 0xd5, 0xe1,
  0xe8, 0xd9, 0xe4, 0xea, 0xd7, 0xe2, 0xe8, 0xe5, 0xec, 0xf0, 0xeb, 0xf0,
  0xf3, 0x84, 0xb0, 0xc7, 0xd1, 0xde, 0xe5, 0xdc, 0xe6, 0xeb, 0xe3, 0xeb,
  0xef, 0xeb, 0xf1, 0xf4, 0xee, 0xf3, 0xf5, 0xf7, 0xfa, 0xfb, 0xfb, 0xfc,
  0xfc, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x2c, 0x01, 0x00, 0x06,
  0xff, 0x40, 0x96, 0x50, 0xb1, 0xc9, 0x60, 0x48, 0x24, 0x21, 0x25, 0x43,
  0x71, 0x00, 0x56, 0x03, 0x16, 0x65, 0x32, 0x1a, 0x58, 0xad, 0x8a, 0xcc,
  0x08, 0x4a, 0x28, 0x08, 0x04, 0x93, 0xc4, 0xa0, 0x2b, 0x80, 0x98, 0x33,
  0x0d, 0x32, 0x24, 0xc0, 0xc6, 0x20, 0xbc, 0x6b, 0x76, 0x8a, 0xe4, 0x2d,
  0xcb, 0xe7, 0xf5, 0x75, 0x2a, 0x85, 0x22, 0x7d, 0xe3, 0x7c, 0x7d, 0x7f,
  0x01, 0x7c, 0x07, 0x07, 0x7e, 0x71, 0x28, 0x0f, 0x22, 0x0c, 0x24, 0x66,
  0x84, 0x07, 0x0c, 0x0c, 0x27, 0x8e, 0x6c, 0x28, 0x8c, 0x26, 0x26, 0x24,
  0x72, 0x91, 0x99, 0x0b, 0x9b, 0x90, 0x0c, 0x26, 0x0b, 0x21, 0xa0, 0x29,
  0x0f, 0xa2, 0xa4, 0x9b, 0x7b, 0xa8, 0xa3, 0xa5, 0x72, 0xad, 0xaa, 0xb0,
  0xa9, 0xaf, 0x84, 0xb1, 0xaf, 0xac, 0xb4, 0xa6, 0xb7, 0xbb, 0xba, 0xb3,
  0xae, 0xab, 0xa7, 0xbe, 0xb6, 0xc3, 0xc2, 0xc0, 0xbf, 0xb2, 0xb9, 0xc7,
  0xc4, 0xcb, 0xc6, 0xb2, 0xcc, 0xc9, 0xce, 0xb5, 0xd2, 0xbd, 0xcd, 0xbc,
  0x84, 0xd4, 0xc8, 0xd3, 0xd7, 0xd0, 0xb8, 0xd9, 0xdd, 0xd5, 0xcf, 0xd9,
  0xca, 0xe2, 0xdc, 0xdf, 0xe3, 0xe7, 0xe6, 0xea, 0xbe, 0xe4, 0xdb, 0xc5,
  0xeb, 0xc7, 0xed, 0xe1, 0xee, 0xd6, 0xec, 0xe9, 0xef, 0xf8, 0xf1, 0xf7,
  0xf5, 0xfc, 0xd1, 0xf0, 0xe5, 0xf9, 0xfc, 0x05, 0xa4, 0x07, 0x50, 0xdf,
  0x3f, 0x82, 0x08, 0x83, 0x1d, 0x9c, 0xc7, 0x10, 0xdb, 0x42, 0x6d, 0x0d,
  0xe5, 0x41, 0x9c, 0x08, 0xce, 0xe1, 0xc0, 0x86, 0x15, 0x25, 0x56, 0xdc,
  0x88, 0xee, 0x21, 0xc7, 0x6b, 0x1a, 0xf7, 0x15, 0x14, 0xd8, 0x2f, 0xe1,
  0xc4, 0x90, 0x1e, 0x3b, 0x5e, 0xa4, 0xa8, 0xb2, 0x24, 0xc6, 0x96, 0x23,
  0x4d, 0x66, 0x14, 0x29, 0x13, 0x66, 0xcd, 0x87, 0x28, 0x57, 0xce, 0x4c,
  0x89, 0x93, 0xe6, 0x4b, 0xe7, 0x90, 0xd2, 0x84, 0xb0, 0x20, 0x92, 0x01,
  0x49, 0x12, 0x29, 0x4c, 0x1c, 0x18, 0x10, 0x3a, 0x65, 0x44, 0x0b, 0xa1,
  0x43, 0xb5, 0xb4, 0x78, 0x2a, 0x34, 0x0c, 0x55, 0xa8, 0x68, 0xa0, 0x0a,
  0x25, 0x11, 0x41, 0xab, 0x90, 0xa3, 0x5e, 0xc1, 0x4e, 0x1d, 0x4b, 0x62,
  0xac, 0xd9, 0x16, 0x65, 0xa7, 0x0e, 0x58, 0xb1, 0x82, 0x00, 0x81, 0xb4,
  0x6b, 0xbb, 0x78, 0x21, 0xc1, 0xd6, 0xed, 0x97, 0x32, 0x74, 0xdd, 0xd6,
  0x09, 0x00, 0x21, 0xaf, 0x9a, 0x35, 0x74, 0xdb, 0xe6, 0xe9, 0x1b, 0x97,
  0xc0, 0x5d, 0x01, 0x24, 0xac, 0xb4, 0x25, 0x83, 0x58, 0xed, 0xe2, 0x2e,
  0x69, 0x5b, 0xac, 0x5d, 0x1c, 0x59, 0xad, 0x95, 0xca, 0x66, 0x8f, 0x9e,
  0x45, 0xeb, 0xf5, 0x6b, 0x67, 0x16, 0x60, 0xb5, 0x86, 0x86, 0x3a, 0x7a,
  0xeb, 0xe7, 0xd2, 0x9e, 0x3b, 0xa3, 0x06, 0x7d, 0xba, 0xb5, 0x6a, 0xd7,
  0x61, 0x61, 0x8b, 0x96, 0x4d, 0x9a, 0xb6, 0xe9, 0xd7, 0xb8, 0x63, 0xe7,
  0x9e, 0xbd, 0xbb, 0x76, 0xef, 0xdb, 0xba, 0x83, 0xf3, 0x16, 0xee, 0x9b,
  0x38, 0xf0, 0xe1, 0xc8, 0x8b, 0x27, 0x3f, 0xae, 0xbc, 0x39, 0xf3, 0xe7,
  0xa9, 0x8d, 0x47, 0x5f, 0x3e, 0xdd, 0x79, 0x75, 0xe8, 0xac, 0x7f, 0x5f,
  0xdf, 0x9e, 0x5d, 0x7a, 0x77, 0xea, 0xdf, 0xad, 0x87, 0xc7, 0xbe, 0xba,
  0xbc, 0x6d, 0xee, 0xe6, 0xb5, 0x8f, 0x47, 0x7f, 0x7e, 0xbd, 0xfb, 0xf4,
  0xde, 0xe1, 0x83, 0x97, 0x2f, 0x9e, 0x3e, 0xf9, 0xf6, 0xf6, 0xd9, 0xab,
  0xcf, 0xff, 0x1e, 0xbf, 0xff, 0xfd, 0xff, 0xc5, 0x17, 0xe0, 0x7c, 0x03,
  0xd6, 0x57, 0xe0, 0x7d, 0x00, 0x76, 0x16, 0x04, 0x00, 0x3b
};
static unsigned int tab_l_gif_len = 706;

static unsigned char tab_r_gif[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x90, 0x01, 0x2c, 0x01, 0xd5, 0x00,
  0x00, 0xf6, 0xf7, 0xf9, 0xf1, 0xf4, 0xf7, 0xf6, 0xf8, 0xfa, 0xfc, 0xfd,
  0xfe, 0xfa, 0xfb, 0xfc, 0xf9, 0xfa, 0xfb, 0xf8, 0xf9, 0xfa, 0xea, 0xef,
  0xf3, 0xef, 0xf3, 0xf6, 0xc6, 0xd5, 0xdf, 0xd2, 0xde, 0xe6, 0xd8, 0xe2,
  0xe9, 0xde, 0xe7, 0xed, 0xdd, 0xe6, 0xec, 0xe5, 0xec, 0xf1, 0xe8, 0xee,
  0xf2, 0xf4, 0xf7, 0xf9, 0xf3, 0xf6, 0xf8, 0xb3, 0xc8, 0xd5, 0xc1, 0xd2,
  0xdd, 0xcb, 0xd9, 0xe2, 0xcf, 0xdc, 0xe4, 0xd6, 0xe1, 0xe8, 0x96, 0xb4,
  0xc5, 0x9d, 0xb9, 0xc9, 0xaf, 0xc2, 0xcd, 0xbb, 0xce, 0xd9, 0xc3, 0xd4,
  0xde, 0xc2, 0xd3, 0xdd, 0xc8, 0xd7, 0xe0, 0xcc, 0xda, 0xe2, 0xd5, 0xe1,
  0xe8, 0xd9, 0xe4, 0xea, 0xd7, 0xe2, 0xe8, 0xe5, 0xec, 0xf0, 0xeb, 0xf0,
  0xf3, 0x84, 0xb0, 0xc7, 0xd1, 0xde, 0xe5, 0xdc, 0xe6, 0xeb, 0xe3, 0xeb,
  0xef, 0xeb, 0xf1, 0xf4, 0xee, 0xf3, 0xf5, 0xf7, 0xfa, 0xfb, 0xfb, 0xfc,
  0xfc, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x90, 0x01, 0x2c, 0x01, 0x00, 0x06,
  0xff, 0x40, 0x92, 0x70, 0x48, 0x2c, 0x1a, 0x8f, 0xc8, 0xa4, 0x72, 0xc9,
  0x6c, 0x3a, 0x9f, 0xd0, 0xa8, 0x74, 0x4a, 0xad, 0x5a, 0xaf, 0xd8, 0xac,
  0x76, 0x0b, 0x95, 0x68, 0x3c, 0xac, 0x70, 0x6b, 0x4c, 0x2e, 0x9b, 0xcf,
  0xe8, 0xb4, 0x7a, 0xcd, 0x6e, 0xbb, 0xdf, 0xf0, 0xb8, 0x7c, 0x4e, 0xaf,
  0xdb, 0xef, 0xf8, 0xbc, 0x7e, 0xcf, 0x77, 0x0f, 0x56, 0x10, 0x16, 0x1a,
  0x17, 0x1c, 0x61, 0x2b, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
  0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a,
  0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0x93, 0x2a, 0x10, 0x01, 0x29, 0x15,
  0x5e, 0x2c, 0x2a, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2,
  0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe,
  0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xb6, 0x10, 0x10, 0x29, 0x0f, 0x27, 0x1d,
  0x17, 0x15, 0xc6, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6,
  0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2,
  0xe3, 0xe4, 0xe5, 0xe6, 0xda, 0xa5, 0x28, 0x22, 0x0c, 0x0c, 0x12, 0x12,
  0x01, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa,
  0xfb, 0xfc, 0xfd, 0xfe, 0xff, 0x00, 0x03, 0x0a, 0x1c, 0x48, 0xb0, 0xa0,
  0xc1, 0x83, 0x08, 0x13, 0xf2, 0x4b, 0x81, 0x22, 0x19, 0x03, 0x13, 0x83,
  0x52, 0x48, 0x9c, 0x48, 0xb1, 0xa2, 0xc5, 0x8b, 0x18, 0x33, 0x6a, 0xdc,
  0xc8, 0xb1, 0xa3, 0xc7, 0x8f, 0x20, 0x43, 0x8a, 0x1c, 0x49, 0xb2, 0xa4,
  0xc9, 0x93, 0x28, 0x53, 0xaa, 0x5c, 0xe9, 0x11, 0xc5, 0x81, 0x75, 0x26,
  0x40, 0x80, 0x20, 0xc1, 0xb2, 0xa6, 0xcd, 0x9b, 0x38, 0x73, 0xea, 0xdc,
  0xc9, 0xb3, 0xa7, 0x4f, 0xff, 0x96, 0x28, 0x1a, 0xc2, 0x04, 0xb1, 0x80,
  0x44, 0xd0, 0xa3, 0x48, 0x93, 0x2a, 0x5d, 0xca, 0xb4, 0xa9, 0xd3, 0xa7,
  0x50, 0xa3, 0x4a, 0x9d, 0x4a, 0xb5, 0xaa, 0xd5, 0xab, 0x58, 0xb3, 0x6a,
  0xdd, 0xca, 0xb5, 0xab, 0xd7, 0xaf, 0x53, 0x0f, 0x38, 0x34, 0xb1, 0x20,
  0x04, 0x89, 0x03, 0x68, 0xd3, 0xaa, 0x5d, 0xcb, 0xb6, 0xad, 0xdb, 0xb7,
  0x70, 0xe3, 0xca, 0x9d, 0x4b, 0xb7, 0xae, 0xdd, 0xbb, 0x78, 0xf3, 0xea,
  0xdd, 0xcb, 0xb7, 0xaf, 0xdf, 0xbf, 0x80, 0x03, 0xd3, 0x7d, 0x20, 0xe2,
  0x44, 0xcc, 0x10, 0x66, 0x1f, 0x28, 0x5e, 0xcc, 0xb8, 0xb1, 0xe3, 0xc7,
  0x90, 0x23, 0x4b, 0x9e, 0x4c, 0xb9, 0xb2, 0xe5, 0xcb, 0x98, 0x33, 0x6b,
  0xde, 0xcc, 0xb9, 0xb3, 0xe7, 0xcf, 0xa0, 0x43, 0x8b, 0x1e, 0x6d, 0xb9,
  0xf0, 0x43, 0xc4, 0x1f, 0x48, 0x9c, 0x58, 0xcd, 0xba, 0xb5, 0xeb, 0xd7,
  0xb0, 0x63, 0xcb, 0x9e, 0x4d, 0xbb, 0xb6, 0xed, 0xdb, 0xb8, 0x73, 0xeb,
  0xde, 0xcd, 0xbb, 0xb7, 0xef, 0xdf, 0xc0, 0x83, 0x0b, 0x1f, 0x4e, 0x1c,
  0xf7, 0xc3, 0x05, 0x1f, 0x4a, 0x94, 0x20, 0xc1, 0xae, 0xb9, 0xf3, 0xe7,
  0xd0, 0xa3, 0x4b, 0x9f, 0x4e, 0xbd, 0xba, 0xf5, 0xeb, 0xd8, 0xb3, 0x6b,
  0xdf, 0xce, 0xbd, 0xbb, 0xf7, 0xef, 0xe0, 0xc3, 0x8b, 0x1f, 0x4f, 0xbe,
  0x3c, 0x76, 0x13, 0x31, 0x91, 0x2b, 0x5f, 0x2e, 0xb3, 0xbd, 0xfb, 0xf7,
  0xf0, 0xe3, 0xcb, 0x9f, 0x4f, 0xbf, 0xbe, 0xfd, 0xfb, 0xf8, 0xf3, 0xeb,
  0xdf, 0xcf, 0xbf, 0xbf, 0xff, 0xff, 0x00, 0x06, 0x28, 0xe0, 0x80, 0x04,
  0x16, 0x98, 0x5f, 0x59, 0xc9, 0x95, 0x40, 0xc1, 0x72, 0x88, 0x35, 0xe8,
  0xe0, 0x83, 0x10, 0x46, 0x28, 0xe1, 0x84, 0x14, 0x56, 0x68, 0xe1, 0x85,
  0x18, 0x66, 0xa8, 0xe1, 0x86, 0x1c, 0x76, 0xe8, 0xff, 0xe1, 0x87, 0x20,
  0x86, 0x28, 0xe2, 0x88, 0x24, 0x96, 0xa8, 0x61, 0x82, 0x14, 0xa4, 0x48,
  0x82, 0x89, 0x2c, 0xb6, 0xe8, 0xe2, 0x8b, 0x30, 0xc6, 0x28, 0xe3, 0x8c,
  0x34, 0xd6, 0x68, 0xe2, 0x07, 0x09, 0x2a, 0xa8, 0x22, 0x8e, 0x3c, 0xf6,
  0xe8, 0xe3, 0x8f, 0x40, 0x06, 0x29, 0xe4, 0x90, 0x44, 0x16, 0x69, 0xe4,
  0x91, 0x48, 0x26, 0xa9, 0xe4, 0x92, 0x4c, 0x36, 0xe9, 0xe4, 0x93, 0x50,
  0x46, 0x29, 0xe5, 0x94, 0x54, 0x26, 0xa9, 0x5c, 0x8a, 0x3b, 0x56, 0xa9,
  0xe5, 0x96, 0x5c, 0x76, 0xe9, 0xe5, 0x97, 0x60, 0x86, 0x29, 0xe6, 0x98,
  0x5a, 0x5e, 0x89, 0x25, 0x09, 0x64, 0xa6, 0xa9, 0xe6, 0x9a, 0x6c, 0xb6,
  0xe9, 0xe6, 0x9b, 0x70, 0xfe, 0x68, 0x66, 0x96, 0x71, 0xd6, 0x69, 0xe7,
  0x9d, 0x78, 0xe6, 0xa9, 0xe7, 0x97, 0x73, 0x52, 0x80, 0xe6, 0x9e, 0x80,
  0x06, 0x2a, 0xe8, 0xa0, 0x84, 0xc2, 0xd9, 0xe7, 0x9f, 0x85, 0x26, 0xaa,
  0xe8, 0xa2, 0x8c, 0x36, 0x3a, 0xe4, 0xa1, 0x8e, 0x46, 0x2a, 0xe9, 0xa4,
  0x94, 0xc6, 0x09, 0x69, 0xa5, 0x98, 0x66, 0xaa, 0xe9, 0xa6, 0x4f, 0x5e,
  0xca, 0xe9, 0xa7, 0xa0, 0x86, 0xca, 0xa9, 0xa7, 0xa2, 0x96, 0x6a, 0xea,
  0xa9, 0x84, 0x92, 0x8a, 0xea, 0xaa, 0xac, 0xb6, 0xca, 0xa6, 0xaa, 0xae,
  0xc6, 0x2a, 0xeb, 0xac, 0x53, 0xc2, 0x4a, 0xeb, 0xad, 0xb8, 0xe6, 0x2a,
  0xa4, 0xad, 0xba, 0xf6, 0xea, 0xeb, 0xac, 0xbc, 0xfe, 0x2a, 0xec, 0xb0,
  0xa5, 0x06, 0x4b, 0xec, 0xb1, 0xc8, 0x56, 0x6a, 0x6c, 0xb2, 0xcc, 0x36,
  0x9b, 0xe8, 0xb2, 0xce, 0x46, 0x2b, 0x2d, 0x9e, 0xd0, 0x4e, 0x6b, 0xed,
  0xb5, 0x6b, 0x56, 0x8b, 0xed, 0xb6, 0xdc, 0x76, 0xa9, 0x6d, 0xb7, 0xe0,
  0x86, 0xdb, 0xa9, 0x8e, 0x74, 0x8a, 0x6b, 0xee, 0xb9, 0x51, 0x7e, 0x8b,
  0xff, 0xee, 0xba, 0xec, 0xf2, 0xa8, 0x6e, 0xbb, 0xf0, 0x9a, 0xfb, 0x6e,
  0xbc, 0xf4, 0x72, 0x3b, 0x6f, 0xbd, 0xf8, 0x4e, 0x7b, 0x6f, 0xbe, 0xfc,
  0x32, 0xbb, 0x6f, 0xbf, 0x00, 0x0f, 0xfb, 0x6f, 0xc0, 0x04, 0xeb, 0x3a,
  0x70, 0xc1, 0x08, 0x03, 0x4b, 0xae, 0x9f, 0x09, 0x37, 0x1c, 0xed, 0xc1,
  0x0e, 0x47, 0x6c, 0x2a, 0xc4, 0x12, 0x57, 0xfc, 0x29, 0xc5, 0x16, 0x67,
  0x8c, 0x29, 0xc6, 0x1a, 0x77, 0x1c, 0x29, 0xc7, 0x1e, 0x87, 0xac, 0x28,
  0xc8, 0x22, 0x97, 0x2c, 0x28, 0xc9, 0x26, 0xa7, 0x9c, 0x27, 0xca, 0x2a,
  0xb7, 0x6c, 0xe9, 0xc2, 0x88, 0xba, 0x2c, 0x33, 0xa5, 0x2c, 0xcf, 0x6c,
  0x33, 0x99, 0x35, 0xdf, 0xac, 0x33, 0x9f, 0x30, 0xef, 0xec, 0xf3, 0xb3,
  0x3d, 0xff, 0x2c, 0x74, 0xa0, 0x39, 0x0f, 0x6d, 0xb4, 0x93, 0x45, 0x1f,
  0xad, 0xb4, 0x95, 0x41, 0x2f, 0xed, 0x74, 0x9b, 0x49, 0x3f, 0x2d, 0x35,
  0x90, 0x51, 0x4f, 0x6d, 0x35, 0x8e, 0x55, 0x5f, 0x3d, 0x75, 0xd6, 0x5a,
  0x3f, 0xcd, 0x75, 0xd7, 0x4b, 0x7f, 0x0d, 0xf6, 0xd1, 0x62, 0x8f, 0x3d,
  0x74, 0xd9, 0x66, 0xff, 0x8c, 0x76, 0xda, 0x3b, 0xaf, 0xcd, 0xf6, 0xcd,
  0x6e, 0xbf, 0x3d, 0x73, 0xdc, 0x72, 0xbb, 0x4c, 0x77, 0xdd, 0x2a, 0xdf,
  0x8d, 0xb7, 0xc9, 0x7a, 0xef, 0x2d, 0x72, 0xdf, 0x7e, 0x7b, 0x0c, 0x78,
  0xe0, 0x1a, 0x0f, 0x4e, 0xb8, 0xc5, 0x86, 0x1f, 0x2e, 0x71, 0xe2, 0x8a,
  0x3b, 0xcc, 0x78, 0xe3, 0x09, 0x3f, 0x0e, 0x79, 0xc1, 0x92, 0x4f, 0x1e,
  0x70, 0xe5, 0x96, 0xf7, 0x8b, 0x79, 0xe6, 0xf9, 0x6e, 0xce, 0x79, 0xbd,
  0x9e, 0x7f, 0x1e, 0x6f, 0xe8, 0xa2, 0xb7, 0x4b, 0x7a, 0xe9, 0xeb, 0x9e,
  0x8e, 0xfa, 0xb9, 0xaa, 0xaf, 0x2e, 0x6e, 0xeb, 0xae, 0x83, 0x0b, 0x7b,
  0xec, 0xf6, 0x36, 0x4d, 0xff, 0xbb, 0xd6, 0xb3, 0xdf, 0x7e, 0x6d, 0xee,
  0xba, 0xeb, 0x6b, 0x7b, 0xef, 0x52, 0xf3, 0x0e, 0xbc, 0xb3, 0xc2, 0x0f,
  0xef, 0xef, 0xef, 0xc6, 0x2b, 0x5d, 0x7c, 0xf2, 0xc7, 0x2e, 0xcf, 0xbc,
  0xc0, 0xc8, 0x3f, 0x2f, 0xb4, 0xf3, 0xd2, 0xfb, 0x4a, 0x7d, 0xf5, 0x06,
  0x47, 0x8f, 0xbd, 0xce, 0xd7, 0x6f, 0x7f, 0x6b, 0xf7, 0xde, 0x2b, 0x8c,
  0x25, 0xc3, 0xe1, 0xab, 0xad, 0x7d, 0xf9, 0x76, 0x9f, 0x8f, 0x7e, 0xde,
  0xea, 0xaf, 0xcf, 0x77, 0xfb, 0xee, 0xff, 0x0d, 0x7f, 0xfc, 0x82, 0xcf,
  0x4f, 0x7f, 0xe1, 0xf6, 0xdf, 0x8f, 0x78, 0xfe, 0xfa, 0x2f, 0xce, 0x7f,
  0xff, 0x8e, 0xfb, 0x1f, 0x00, 0x23, 0x27, 0xc0, 0x01, 0x52, 0xae, 0x80,
  0x06, 0xbc, 0x1c, 0x02, 0x13, 0xa8, 0xb9, 0x05, 0x32, 0xb0, 0x73, 0x0e,
  0x7c, 0x20, 0xe8, 0x22, 0x28, 0xc1, 0xd1, 0x51, 0xb0, 0x82, 0xa6, 0xbb,
  0x20, 0x06, 0x53, 0xa7, 0xc1, 0x0d, 0xb2, 0xae, 0x83, 0x1e, 0x7c, 0x1d,
  0x08, 0x43, 0x28, 0xbb, 0x11, 0x92, 0xb0, 0x76, 0xe3, 0x8b, 0xd9, 0x09,
  0x09, 0x98, 0xc2, 0x15, 0x46, 0x0c, 0x7c, 0x2e, 0x64, 0x14, 0x0c, 0x63,
  0x38, 0x32, 0x13, 0xd2, 0x50, 0x5a, 0x33, 0xbc, 0x61, 0xaa, 0x6c, 0xa8,
  0xc3, 0x66, 0xe5, 0xb0, 0x87, 0x44, 0xe3, 0x21, 0x10, 0x91, 0xf5, 0xc3,
  0x21, 0xea, 0xa9, 0x88, 0x46, 0xa4, 0x96, 0x10, 0x93, 0x28, 0x2c, 0x24,
  0x32, 0xb1, 0x4e, 0x4e, 0x7c, 0xa2, 0xa1, 0x96, 0x28, 0xc5, 0xec, 0xb5,
  0xb0, 0x8a, 0x16, 0x4c, 0x21, 0x17, 0xb6, 0xc8, 0xc5, 0x2e, 0x7a, 0xf1,
  0x8b, 0x60, 0x0c, 0xa3, 0x18, 0xc7, 0x48, 0xc6, 0x2e, 0x7a, 0x01, 0x0c,
  0x61, 0x48, 0xa3, 0x1a, 0xd7, 0xc8, 0xc6, 0x36, 0xba, 0xf1, 0x8d, 0x70,
  0x8c, 0xa3, 0x1c, 0xe7, 0x48, 0xc7, 0x3a, 0xda, 0xff, 0xf1, 0x8e, 0x78,
  0xcc, 0xa3, 0x1e, 0xf7, 0xc8, 0xc7, 0x3e, 0xfa, 0xf1, 0x8f, 0x80, 0x0c,
  0x64, 0x1d, 0xc7, 0x40, 0x80, 0x00, 0x08, 0x82, 0x10, 0x82, 0x4c, 0xa4,
  0x22, 0x17, 0xc9, 0xc8, 0x46, 0x3a, 0xf2, 0x91, 0x90, 0x8c, 0xa4, 0x24,
  0x13, 0x39, 0x86, 0x02, 0x08, 0x20, 0x00, 0x28, 0x38, 0x85, 0x06, 0x26,
  0xc9, 0xc9, 0x4e, 0x7a, 0xf2, 0x93, 0xa0, 0x0c, 0xa5, 0x28, 0x47, 0xa9,
  0x46, 0x42, 0x5e, 0xb2, 0x21, 0xcb, 0xa8, 0x00, 0x29, 0x57, 0xc9, 0xca,
  0x56, 0xba, 0xf2, 0x95, 0xb0, 0x6c, 0xa4, 0x29, 0x31, 0x99, 0x0c, 0x77,
  0xc4, 0xf2, 0x96, 0xb8, 0xcc, 0xa5, 0x2e, 0x77, 0x19, 0xca, 0x59, 0xba,
  0xe4, 0x01, 0x83, 0xe0, 0xa5, 0x30, 0x87, 0x49, 0xcc, 0x62, 0x1a, 0xf3,
  0x8d, 0xbe, 0x7c, 0xc9, 0x03, 0x48, 0x70, 0xcc, 0x66, 0x3a, 0xf3, 0x99,
  0xd0, 0xec, 0x65, 0x0b, 0x08, 0x70, 0x4a, 0xb1, 0x88, 0x80, 0x04, 0x7d,
  0xc8, 0xa6, 0x36, 0xb7, 0xc9, 0xcd, 0x6e, 0x7a, 0xf3, 0x9b, 0xe0, 0x0c,
  0xa7, 0x38, 0xfb, 0x30, 0x00, 0x02, 0x90, 0xc2, 0x25, 0x22, 0xb8, 0xe6,
  0x38, 0xd7, 0xc9, 0xce, 0x76, 0xba, 0xf3, 0x9d, 0xf0, 0x8c, 0xa7, 0x3c,
  0xc9, 0x50, 0xce, 0x51, 0x60, 0xf2, 0x25, 0xd7, 0x24, 0x80, 0x3e, 0xf7,
  0xc9, 0xcf, 0x7e, 0xfa, 0xf3, 0x9f, 0x00, 0x0d, 0xa8, 0x40, 0x07, 0x4a,
  0xd0, 0x82, 0x1a, 0xf4, 0xa0, 0x08, 0x4d, 0xa8, 0x42, 0x17, 0xca, 0xd0,
  0x86, 0x3a, 0xf4, 0xa1, 0x10, 0x8d, 0xa8, 0x44, 0x27, 0x5a, 0x50, 0x4b,
  0x46, 0x20, 0x05, 0xd6, 0xbc, 0x26, 0x31, 0x36, 0xca, 0xd1, 0x8e, 0x7a,
  0xf4, 0xa3, 0x20, 0x0d, 0xa9, 0x48, 0x47, 0x4a, 0x52, 0x62, 0x08, 0x20,
  0x02, 0xf7, 0x4c, 0xe7, 0x35, 0xcf, 0xc1, 0xd2, 0x96, 0xba, 0xf4, 0xa5,
  0xff, 0x30, 0x8d, 0xa9, 0x4c, 0x67, 0x4a, 0xd3, 0x9a, 0x9a, 0x23, 0x02,
  0x28, 0x65, 0x08, 0x3e, 0xaf, 0x89, 0xd3, 0x9e, 0xfa, 0xf4, 0xa7, 0x40,
  0x0d, 0xaa, 0x50, 0x87, 0x4a, 0xd4, 0xa2, 0x1a, 0xf5, 0xa8, 0x48, 0x4d,
  0xaa, 0x52, 0x97, 0xca, 0xd4, 0xa6, 0x3a, 0xf5, 0xa9, 0x50, 0x8d, 0xaa,
  0x54, 0xa7, 0x4a, 0xd5, 0xaa, 0x26, 0x35, 0x1d, 0x3b, 0x25, 0x81, 0x55,
  0xb7, 0xca, 0xd5, 0xae, 0x7a, 0xf5, 0xab, 0x60, 0x0d, 0xab, 0x58, 0xc7,
  0x4a, 0x56, 0xab, 0xc2, 0x43, 0xa7, 0x8b, 0xd1, 0x6a, 0x59, 0xd7, 0xca,
  0xd6, 0xb6, 0xba, 0xf5, 0xad, 0x70, 0x8d, 0xab, 0x5c, 0x7f, 0x8a, 0x55,
  0xb4, 0x90, 0xc0, 0xa6, 0x78, 0xcd, 0xab, 0x5e, 0xf7, 0xca, 0xd7, 0xbe,
  0xfa, 0xf5, 0xaf, 0xd0, 0xc0, 0x69, 0x29, 0x24, 0x82, 0x02, 0x12, 0x94,
  0xf4, 0xb0, 0x88, 0x4d, 0xac, 0x62, 0x17, 0xcb, 0xd8, 0xc6, 0x3a, 0x76,
  0x15, 0x02, 0x88, 0x2c, 0x04, 0x04, 0x0b, 0x0f, 0x12, 0x14, 0xe0, 0xb2,
  0x98, 0xcd, 0xac, 0x66, 0x37, 0xcb, 0xd9, 0xce, 0x7a, 0xf6, 0xb3, 0xa0,
  0x0d, 0xad, 0x68, 0x47, 0x4b, 0xda, 0xd2, 0x9a, 0xf6, 0xb4, 0xa8, 0x4d,
  0xad, 0x6a, 0x57, 0xcb, 0xda, 0xd6, 0xba, 0xf6, 0xb5, 0xb0, 0x15, 0xad,
  0x2a, 0x24, 0xdb, 0x53, 0x12, 0x50, 0xf4, 0xb6, 0xb8, 0xcd, 0xad, 0x6e,
  0x77, 0xcb, 0xdb, 0xde, 0xfa, 0xf6, 0xb7, 0xc0, 0xc5, 0x6d, 0x01, 0x20,
  0x2b, 0x00, 0x12, 0x84, 0xe2, 0xb8, 0xc8, 0x4d, 0xae, 0x72, 0x97, 0xcb,
  0xdc, 0xe6, 0x3a, 0xf7, 0xb9, 0xd0, 0x45, 0xae, 0x3f, 0xb1, 0x39, 0xcf,
  0xea, 0x5a, 0xf7, 0xba, 0xd8, 0xcd, 0xae, 0x76, 0xbf, 0x39, 0x80, 0xee,
  0x22, 0x82, 0xba, 0xdb, 0x0d, 0xaf, 0x78, 0xc7, 0x4b, 0xde, 0xf2, 0x62,
  0x97, 0x99, 0xd1, 0x4c, 0xff, 0xaf, 0x7a, 0xd7, 0xcb, 0x5e, 0x41, 0xa2,
  0xb7, 0xbd, 0xf0, 0x8d, 0xaf, 0x7c, 0xe7, 0x1b, 0x86, 0xf7, 0xd2, 0xf7,
  0xbe, 0xf8, 0xcd, 0xaf, 0x30, 0xed, 0xab, 0xdf, 0xfe, 0xfa, 0xf7, 0xbf,
  0xa1, 0xe4, 0x2f, 0x80, 0x07, 0x4c, 0xe0, 0x02, 0xbb, 0xd7, 0xc0, 0x08,
  0x4e, 0xb0, 0x82, 0xef, 0x28, 0xe0, 0x05, 0x3b, 0xf8, 0xc1, 0x09, 0x6e,
  0x30, 0x84, 0x27, 0x4c, 0x61, 0xfd, 0x4a, 0xb8, 0xc2, 0x18, 0xce, 0x30,
  0x7b, 0x2f, 0xac, 0xe1, 0x0e, 0x7b, 0xd8, 0x98, 0x1c, 0xfe, 0xb0, 0x88,
  0x47, 0x7c, 0xcb, 0x10, 0x93, 0xf8, 0xc4, 0x28, 0x16, 0xa5, 0x89, 0x53,
  0xcc, 0xe2, 0x16, 0x43, 0x72, 0xc5, 0x2e, 0x8e, 0xb1, 0x8c, 0x01, 0x09,
  0xe3, 0x19, 0xdb, 0xf8, 0xc6, 0x76, 0xac, 0x31, 0x8e, 0x77, 0xcc, 0x63,
  0x36, 0xea, 0xb8, 0xc7, 0x40, 0xde, 0xf1, 0x8f, 0x83, 0x4c, 0x64, 0x19,
  0x0f, 0xb9, 0xc8, 0x48, 0x4e, 0xf1, 0x91, 0x93, 0xcc, 0x64, 0x11, 0x2f,
  0xb9, 0xc9, 0x50, 0xce, 0xf0, 0x93, 0xa3, 0x4c, 0x65, 0x08, 0x4f, 0xb9,
  0xca, 0x58, 0x8e, 0x70, 0x96, 0xb7, 0x7c, 0xe2, 0x2b, 0x73, 0xf9, 0xcb,
  0xfd, 0xf5, 0x32, 0x98, 0xc7, 0x4c, 0x5f, 0x31, 0x93, 0xf9, 0xcc, 0xed,
  0x35, 0x33, 0x9a, 0xd7, 0x1c, 0x4d, 0x35, 0xb3, 0xf9, 0xcd, 0xc7, 0x74,
  0x33, 0x9c, 0xe7, 0xbc, 0x5f, 0x3a, 0xdb, 0xd9, 0xc2, 0x77, 0xce, 0x73,
  0x99, 0xf5, 0xcc, 0x67, 0xf8, 0xca, 0xb9, 0xcf, 0x80, 0x0e, 0x70, 0xa0,
  0x07, 0xfd, 0xcc, 0x3f, 0x13, 0xfa, 0xd0, 0x2f, 0x46, 0xb4, 0xa2, 0xeb,
  0xbc, 0xe8, 0x46, 0xe3, 0xd2, 0xd0, 0x8e, 0x8e, 0x74, 0x1f, 0x21, 0x2d,
  0xe9, 0x4a, 0xe3, 0x91, 0xd2, 0x96, 0xce, 0xf4, 0x1c, 0x31, 0xad, 0xe9,
  0x4e, 0xbb, 0x91, 0xd3, 0x9e, 0x0e, 0x75, 0x1a, 0xff, 0x41, 0x2d, 0xea,
  0x50, 0x93, 0xba, 0xd4, 0x9d, 0x3e, 0x35, 0xaa, 0x33, 0xad, 0xea, 0x55,
  0x57, 0xba, 0xd5, 0xae, 0x8e, 0x34, 0xac, 0x63, 0xdd, 0xe8, 0x59, 0xd3,
  0x5a, 0xd1, 0xb6, 0xbe, 0xf5, 0xa1, 0x73, 0xad, 0xeb, 0x41, 0xf3, 0xba,
  0xd7, 0x80, 0xfe, 0x35, 0xb0, 0xf9, 0x2c, 0xec, 0x61, 0xe7, 0xb9, 0xd8,
  0xc6, 0xb6, 0x33, 0xb2, 0x93, 0x3d, 0xe7, 0x65, 0x33, 0xfb, 0xcd, 0xce,
  0x7e, 0xf6, 0x9a, 0xa3, 0x2d, 0xed, 0x33, 0x53, 0xbb, 0xda, 0x63, 0xbe,
  0x36, 0xb6, 0xbf, 0xac, 0xed, 0x6d, 0x6f, 0xb9, 0xdb, 0xde, 0xc6, 0x32,
  0xb8, 0xc3, 0x4d, 0xe5, 0x71, 0x93, 0x1b, 0xca, 0xe6, 0x3e, 0x37, 0x93,
  0xd3, 0xad, 0x6e, 0x24, 0xb3, 0xbb, 0xdd, 0x44, 0x7e, 0x37, 0xbc, 0x81,
  0x2c, 0xef, 0x79, 0xf3, 0xb8, 0xde, 0xf6, 0xc6, 0x31, 0xbe, 0xf3, 0x6d,
  0xe3, 0x7d, 0xf3, 0xdb, 0xc8, 0xff, 0x76, 0xb5, 0xbf, 0x03, 0xde, 0xe2,
  0x81, 0x13, 0x5c, 0xc9, 0x07, 0x2f, 0xb5, 0xc1, 0x13, 0x4e, 0xe2, 0x85,
  0x33, 0xdc, 0xc9, 0x0f, 0xf7, 0xb4, 0xc3, 0x23, 0xde, 0xe1, 0x89, 0x53,
  0x5c, 0xca, 0x17, 0x67, 0x75, 0xc6, 0x2d, 0x6d, 0xf1, 0x8d, 0x4f, 0xb8,
  0xe3, 0x1e, 0x7f, 0x30, 0xc8, 0x43, 0xbe, 0xe0, 0x91, 0x93, 0x5c, 0xcb,
  0x27, 0x5f, 0xb4, 0xc9, 0x53, 0x5e, 0xe0, 0x95, 0xb3, 0x7c, 0xc0, 0x2e,
  0x7f, 0xf9, 0x7f, 0x63, 0x2e, 0xf3, 0x30, 0xd7, 0x9c, 0xd0, 0x34, 0xbf,
  0x39, 0x7e, 0x73, 0xae, 0xf3, 0x3d, 0xf7, 0xbc, 0xcf, 0x3c, 0xff, 0x79,
  0x7c, 0x83, 0x2e, 0xf4, 0x34, 0x17, 0x5d, 0xcf, 0x44, 0x3f, 0xba, 0x7a,
  0x93, 0xae, 0xf4, 0x36, 0x37, 0x5d, 0xd9, 0x4f, 0xa7, 0x33, 0xd3, 0xa3,
  0xde, 0xcc, 0xa9, 0x53, 0x1d, 0xc4, 0x57, 0x87, 0x76, 0xd6, 0xd9, 0x6c,
  0x3e, 0xf5, 0xad, 0x33, 0xda, 0xeb, 0x64, 0xee, 0x3a, 0xd8, 0x75, 0x29,
  0xf6, 0xb1, 0x3f, 0xda, 0xec, 0xd9, 0x46, 0x3b, 0x98, 0xcb, 0xae, 0xf6,
  0x57, 0xb2, 0xbd, 0xed, 0xad, 0x7c, 0x3b, 0xdc, 0x57, 0x29, 0xf7, 0xb9,
  0x8f, 0xb2, 0xee, 0x76, 0x17, 0x74, 0xde, 0xcb, 0xbd, 0x77, 0xbe, 0xf7,
  0x1d, 0xdd, 0x7f, 0x07, 0x7c, 0xe0, 0xd7, 0x3d, 0x78, 0xc2, 0x17, 0xde,
  0xdd, 0x41, 0x00, 0x00, 0x3b
};
static unsigned int tab_r_gif_len = 2585;


static const char tabs_css[] = 
"/* tabs styles, based on http://www.alistapart.com/articles/slidingdoors */\n"
"\n"
"DIV.tabs\n"
"{\n"
"   float            : left;\n"
"   width            : 100%;\n"
"   background       : url(\"tab_b.gif\") repeat-x bottom;\n"
"   margin-bottom    : 4px;\n"
"}\n"
"\n"
"DIV.tabs UL\n"
"{\n"
"   margin           : 0px;\n"
"   padding-left     : 10px;\n"
"   list-style       : none;\n"
"}\n"
"\n"
"DIV.tabs LI, DIV.tabs FORM\n"
"{\n"
"   display          : inline;\n"
"   margin           : 0px;\n"
"   padding          : 0px;\n"
"}\n"
"\n"
"DIV.tabs FORM\n"
"{\n"
"   float            : right;\n"
"}\n"
"\n"
"DIV.tabs A\n"
"{\n"
"   float            : left;\n"
"   background       : url(\"tab_r.gif\") no-repeat right top;\n"
"   border-bottom    : 1px solid #84B0C7;\n"
"   font-size        : x-small;\n"
"   font-weight      : bold;\n"
"   text-decoration  : none;\n"
"}\n"
"\n"
"DIV.tabs A:hover\n"
"{\n"
"   background-position: 100% -150px;\n"
"}\n"
"\n"
"DIV.tabs A:link, DIV.tabs A:visited,\n"
"DIV.tabs A:active, DIV.tabs A:hover\n"
"{\n"
"       color: #1A419D;\n"
"}\n"
"\n"
"DIV.tabs SPAN\n"
"{\n"
"   float            : left;\n"
"   display          : block;\n"
"   background       : url(\"tab_l.gif\") no-repeat left top;\n"
"   padding          : 5px 9px;\n"
"   white-space      : nowrap;\n"
"}\n"
"\n"
"DIV.tabs INPUT\n"
"{\n"
"   float            : right;\n"
"   display          : inline;\n"
"   font-size        : 1em;\n"
"}\n"
"\n"
"DIV.tabs TD\n"
"{\n"
"   font-size        : x-small;\n"
"   font-weight      : bold;\n"
"   text-decoration  : none;\n"
"}\n"
"\n"
"\n"
"\n"
"/* Commented Backslash Hack hides rule from IE5-Mac \\*/\n"
"DIV.tabs SPAN {float : none;}\n"
"/* End IE5-Mac hack */\n"
"\n"
"DIV.tabs A:hover SPAN\n"
"{\n"
"   background-position: 0% -150px;\n"
"}\n"
"\n"
"DIV.tabs LI.current A\n"
"{\n"
"   background-position: 100% -150px;\n"
"   border-width     : 0px;\n"
"}\n"
"\n"
"DIV.tabs LI.current SPAN\n"
"{\n"
"   background-position: 0% -150px;\n"
"   padding-bottom   : 6px;\n"
"}\n"
"\n"
"DIV.navpath\n"
"{\n"
"   background       : none;\n"
"   border           : none;\n"
"   border-bottom    : 1px solid #84B0C7;\n"
"}\n"
;

struct tab_data_item
{
  const char *name;
  unsigned char *content;
  unsigned int len;
};

static tab_data_item tab_data[] =
{
  { "tab_b.gif", tab_b_gif, tab_b_gif_len },
  { "tab_l.gif", tab_l_gif, tab_l_gif_len },
  { "tab_r.gif", tab_r_gif, tab_r_gif_len },
  { "tabs.css",  (unsigned char *)tabs_css, 0 }, 
  { 0, 0, 0 }
};

static void writeTabData(const char *dir)
{
  tab_data_item *data = tab_data;
  while (data->name)
  {
    QCString fileName;
    fileName=(QCString)dir+"/"+data->name;
    QFile f(fileName);
    if (f.open(IO_WriteOnly))
    {
      f.writeBlock((char*)data->content,
                    data->len>0 ? data->len : strlen((char*)data->content));
    }
    else
    {
      fprintf(stderr,"Warning: Cannot open file %s for writing\n",data->name);
    }
    data++;
  }
}

//------------------------------------------------------------------------

unsigned char open_gif[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x09, 0x00, 0x09, 0x00, 0xf0, 0x00,
  0x00, 0x8e, 0xaf, 0xc4, 0x00, 0x00, 0x00, 0x21, 0xf9, 0x04, 0x01, 0x00,
  0x00, 0x01, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x09, 0x00,
  0x00, 0x02, 0x0d, 0x8c, 0x8f, 0xa9, 0xcb, 0xe0, 0xff, 0x02, 0x8c, 0x66,
  0x26, 0x7a, 0x51, 0x01, 0x00, 0x3b
};
unsigned int open_gif_len = 54;

unsigned char closed_gif[] = {
  0x47, 0x49, 0x46, 0x38, 0x39, 0x61, 0x09, 0x00, 0x09, 0x00, 0xf0, 0x00,
  0x00, 0x8e, 0xaf, 0xc4, 0x00, 0x00, 0x00, 0x21, 0xf9, 0x04, 0x01, 0x00,
  0x00, 0x01, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x09, 0x00,
  0x00, 0x02, 0x10, 0x8c, 0x03, 0xa7, 0x98, 0xcb, 0xad, 0x80, 0x84, 0x66,
  0xca, 0x38, 0x57, 0xd6, 0xf4, 0xd0, 0x02, 0x00, 0x3b
};
unsigned int closed_gif_len = 57;



//------------------------- Pictures for the Tabs ------------------------

HtmlGenerator::HtmlGenerator() : OutputGenerator()
{
  dir=Config_getString("HTML_OUTPUT");
  col=0;  
}

HtmlGenerator::~HtmlGenerator()
{
  //printf("HtmlGenerator::~HtmlGenerator()\n");
}

void HtmlGenerator::init()
{
  QCString dname=Config_getString("HTML_OUTPUT");
  QDir d(dname);
  if (!d.exists() && !d.mkdir(dname))
  {
    err("Could not create output directory %s\n",dname.data());
    exit(1);
  }
  writeLogo(dname);
  if (!Config_getString("HTML_HEADER").isEmpty()) 
  {
    g_header=fileToString(Config_getString("HTML_HEADER"));
    //printf("g_header='%s'\n",g_header.data());
  }
  if (!Config_getString("HTML_FOOTER").isEmpty()) 
  {
    g_footer=fileToString(Config_getString("HTML_FOOTER"));
    //printf("g_footer='%s'\n",g_footer.data());
  }
  createSubDirs(d);

  //if (Config_getBool("HTML_FANCY_TABS"))
  {
    writeTabData(dname);
  }
}

void HtmlGenerator::writeStyleSheetFile(QFile &file)
{
  QTextStream t(&file);
  t << defaultStyleSheet;
}

static void writeDefaultHeaderFile(QTextStream &t, const char *title,
                                   const char *relPath,bool usePathCmd)
{
  QString relPathStr;
  if (usePathCmd) 
    relPathStr="$relpath$";
  else
    relPathStr=relPath;

  t << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n"
    "<html><head>" 
    "<meta http-equiv=\"Content-Type\" content=\"text/html;charset=UTF-8" 
         //<< theTranslator->idLanguageCharset() 
         << "\">\n"
    "<title>"; 
  t << convertToHtml(title);
  t << "</title>\n";
  t << "<link ";
  t << "href=\"";
  if (Config_getString("HTML_STYLESHEET").isEmpty())
  {
    t << relPathStr << "doxygen.css";
  }
  else
  {
    QCString cssname=Config_getString("HTML_STYLESHEET");
    QFileInfo cssfi(cssname);
    if (!cssfi.exists())
    {
      err("Error: user specified HTML style sheet file does not exist!\n");
    }
    t << relPathStr << cssfi.fileName();
  }
  
  t << "\" rel=\"stylesheet\" type=\"text/css\">\n";
  t << "<link href=\"" << relPathStr << "tabs.css\" rel=\"stylesheet\" type=\"text/css\">\n";
  t << "</head><body>\n";
}


void HtmlGenerator::writeHeaderFile(QFile &file)
{
  QTextStream t(&file);
  t.setEncoding(QTextStream::UnicodeUTF8);
  writeDefaultHeaderFile(t,"$title",relativePathToRoot(0),TRUE);
}

void HtmlGenerator::writeFooterFile(QFile &file)
{
  QTextStream t(&file);
  t << "<hr size=\"1\"><address style=\"text-align: right;\"><small>\n";
  t << theTranslator->trGeneratedAt( "$datetime", "$projectname" );
  t << "&nbsp;<a href=\"http://www.doxygen.org/index.html\">"
    << "<img src=\"doxygen.png\" alt=\"doxygen\" " 
    << "align=\"middle\" border=\"0\">"
    << "</a> $doxygenversion";
  t << "</small></address>\n"
    << "</body>\n"
    << "</html>\n";
}

static void generateDynamicSections(QTextStream &t,const QCString &relPath)
{
  if (Config_getBool("HTML_DYNAMIC_SECTIONS"))
  { 
    t << 
      "<script type=\"text/javascript\">\n"
      "<!--\n"
      "function changeDisplayState (e){\n"
      "  var num=this.id.replace(/[^[0-9]/g,'');\n"
      "  var button=this.firstChild;\n"
      "  var sectionDiv=document.getElementById('dynsection'+num);\n"
      "  if (sectionDiv.style.display=='none'||sectionDiv.style.display==''){\n"
      "    sectionDiv.style.display='block';\n"
      "    button.src='" << relPath << "open.gif';\n"
      "  }else{\n"
      "    sectionDiv.style.display='none';\n"
      "    button.src='" << relPath << "closed.gif';\n"
      "  }\n"
      "}\n"
      "function initDynSections(){\n"
      "  var divs=document.getElementsByTagName('div');\n"
      "  var sectionCounter=1;\n"
      "  for(var i=0;i<divs.length-1;i++){\n"
      "    if(divs[i].className=='dynheader'&&divs[i+1].className=='dynsection'){\n"
      "      var header=divs[i];\n"
      "      var section=divs[i+1];\n"
      "      var button=header.firstChild;\n"
      "      if (button!='IMG'){\n"
      "        divs[i].insertBefore(document.createTextNode(' '),divs[i].firstChild);\n"
      "        button=document.createElement('img');\n"
      "        divs[i].insertBefore(button,divs[i].firstChild);\n"
      "      }\n"
      "      header.style.cursor='pointer';\n"
      "      header.onclick=changeDisplayState;\n"
      "      header.id='dynheader'+sectionCounter;\n"
      "      button.src='" << relPath << "closed.gif';\n"
      "      section.id='dynsection'+sectionCounter;\n"
      "      section.style.display='none';\n"
      "      section.style.marginLeft='14px';\n"
      "      sectionCounter++;\n"
      "    }\n"
      "  }\n"
      "}\n"
      "window.onload = initDynSections;\n"
      "-->\n"
      "</script>\n";
  }
}


void HtmlGenerator::startFile(const char *name,const char *,
                              const char *title)
{
  //printf("HtmlGenerator::startFile(%s)\n",name);
  QCString fileName=name;
  lastTitle=title;
  relPath = relativePathToRoot(fileName);

  if (fileName.right(Doxygen::htmlFileExtension.length())!=Doxygen::htmlFileExtension) 
  {
    fileName+=Doxygen::htmlFileExtension;
  }
  startPlainFile(fileName);
  Doxygen::indexList.addIndexFile(fileName);
  //if (Config_getBool("GENERATE_HTMLHELP"))
  //{
  //  HtmlHelp::getInstance()->addIndexFile(fileName);
  //}
  
  QCString dispTitle = title;
  QCString projName = Config_getString("PROJECT_NAME");
  if (!projName.isEmpty())
  {
    dispTitle.prepend(projName+": ");
  }
 
  lastFile = fileName;
  if (g_header.isEmpty()) 
  {
    writeDefaultHeaderFile(t,dispTitle,relPath,FALSE);
  }
  else
  {
    t << substituteKeywords(g_header,convertToHtml(dispTitle),relPath);
  }
  t << "<!-- " << theTranslator->trGeneratedBy() << " Doxygen " 
    << versionString << " -->" << endl;
  generateDynamicSections(t,relPath);
}

static void writePageFooter(QTextStream &t,const QCString &lastTitle,
                            const QCString relPath)
{
  if (g_footer.isEmpty())
  {
    t << "<hr size=\"1\"><address style=\"text-align: right;\"><small>";
    t << theTranslator->trGeneratedAt(
        dateToString(TRUE),
        Config_getString("PROJECT_NAME")
        );
    t << "&nbsp;" << endl << "<a href=\"http://www.doxygen.org/index.html\">";
    t << endl << "<img src=\"" << relPath << "doxygen.png\" alt=\"doxygen\" " 
      << "align=\"middle\" border=\"0\">" << "</a> " << versionString << " ";
    t << "</small></address>";
    if (Debug::isFlagSet(Debug::Validate))
    {
      t << "<p><a href=\"http://validator.w3.org/check/referer\">"
           "<img border=\"0\" src=\"http://www.w3.org/Icons/valid-html401\""
           " height=\"31\" width=\"88\" alt=\"This page is Valid HTML 4.01 "
           "Transitional!\"></a><a href=\"http://jigsaw.w3.org/css-validator/\">"
           "<img style=\"border:0;width:88px;height:31px\" "
           "src=\"http://jigsaw.w3.org/css-validator/images/vcss\" "
           "alt=\"This page uses valid CSS!\"></a></p>";
    }
    t << "\n</body>\n</html>\n";
  }
  else
  {
    t << substituteKeywords(g_footer,convertToHtml(lastTitle),relPath);
  }
}

void HtmlGenerator::writeFooter()
{
  writePageFooter(t,lastTitle,relPath);
}

void HtmlGenerator::endFile()
{
  endPlainFile();
}

void HtmlGenerator::startProjectNumber()
{
  t << "<h3 align=\"center\">";
}

void HtmlGenerator::endProjectNumber()
{
  t << "</h3>";
}

void HtmlGenerator::writeStyleInfo(int part)
{
  //printf("writeStyleInfo(%d)\n",part);
  if (part==0)
  {
    if (Config_getString("HTML_STYLESHEET").isEmpty()) // write default style sheet
    {
      //printf("write doxygen.css\n");
      startPlainFile("doxygen.css"); 
      
      // alternative, cooler looking titles
      //t << "H1 { text-align: center; border-width: thin none thin none;" << endl;
      //t << "     border-style : double; border-color : blue; padding-left : 1em; padding-right : 1em }" << endl;

      t << defaultStyleSheet;
      endPlainFile();
    }
    else // write user defined style sheet
    {
      QCString cssname=Config_getString("HTML_STYLESHEET");
      QFileInfo cssfi(cssname);
      if (!cssfi.exists() || !cssfi.isFile() || !cssfi.isReadable())
      {
        err("Error: style sheet %s does not exist or is not readable!", Config_getString("HTML_STYLESHEET").data());
      }
      else
      {
        // convert style sheet to string
        QCString fileStr = fileToString(cssname);
        // write the string into the output dir
        startPlainFile(cssfi.fileName());
        t << fileStr;
        endPlainFile();
      }
    }
  }
}

void HtmlGenerator::startDoxyAnchor(const char *,const char *,
                                    const char *anchor, const char *name,
                                    const char *args)
{
  t << "<a class=\"anchor\" name=\"" << anchor << "\"></a>";
  t << "<!-- doxytag: member=\"";
  docify(name,TRUE); 
  t << "\" ref=\""; 
  docify(anchor,TRUE); 
  t << "\" args=\"";
  docify(args,TRUE);
  t << "\" -->";
}

void HtmlGenerator::endDoxyAnchor(const char *,const char *)
{
}

void HtmlGenerator::newParagraph()
{
  t << endl << "<p>" << endl;
}

void HtmlGenerator::startParagraph()
{
  t << endl << "<p>";
}

void HtmlGenerator::endParagraph()
{
  t << "</p>" << endl;
}

void HtmlGenerator::writeString(const char *text)
{
  t << text;
}

void HtmlGenerator::startIndexItem(const char *ref,const char *f)
{
  //printf("HtmlGenerator::startIndexItem(%s,%s)\n",ref,f);
  QCString *dest;
  t << "<li>";
  if (ref || f)
  {
    if (ref) 
    {
      t << "<a class=\"elRef\" ";
      t << "doxygen=\"" << ref << ":";
      if ((dest=Doxygen::tagDestinationDict[ref])) t << *dest << "/";
      t << "\" ";
    }
    else
    {
      t << "<a class=\"el\" ";
    }
    t << "href=\"";
    if (ref)
    {
      if ((dest=Doxygen::tagDestinationDict[ref])) t << *dest << "/";
    }
    else
    {
      t << relPath;
    }
    if (f) t << f << Doxygen::htmlFileExtension << "\">";
  }
  else
  {
    t << "<b>";
  }
}

void HtmlGenerator::endIndexItem(const char *ref,const char *f)
{
  //printf("HtmlGenerator::endIndexItem(%s,%s,%s)\n",ref,f,name);
  if (ref || f)
  {
    t << "</a>" << endl;
  }
  else
  {
    t << "</b>";
  }
}

void HtmlGenerator::writeStartAnnoItem(const char *,const char *f,
                                       const char *path,const char *name)
{
  t << "<li>";
  if (path) docify(path);
  t << "<a class=\"el\" href=\"" << f << Doxygen::htmlFileExtension << "\">";
  docify(name);
  t << "</a> ";
}

void HtmlGenerator::writeObjectLink(const char *ref,const char *f,
                                    const char *anchor, const char *name)
{
  QCString *dest;
  if (ref) 
  {
    t << "<a class=\"elRef\" ";
    t << "doxygen=\"" << ref << ":";
    if ((dest=Doxygen::tagDestinationDict[ref])) t << *dest << "/";
    t << "\" ";
  }
  else
  {
    t << "<a class=\"el\" ";
  }
  t << "href=\"";
  if (ref)
  {
    if ((dest=Doxygen::tagDestinationDict[ref])) t << relPath << *dest << "/";
  }
  else
  {
    t << relPath;
  }
  if (f) t << f << Doxygen::htmlFileExtension;
  if (anchor) t << "#" << anchor;
  t << "\">";
  docify(name);
  t << "</a>";
}

void HtmlGenerator::writeCodeLink(const char *ref,const char *f,
                                  const char *anchor, const char *name,
                                  const char *tooltip)
{
  QCString *dest;
  //printf("writeCodeLink(ref=%s,f=%s,anchor=%s,name=%s,tooltip=%s)\n",ref,f,anchor,name,tooltip);
  if (ref) 
  {
    t << "<a class=\"codeRef\" ";
    t << "doxygen=\"" << ref << ":";
    if ((dest=Doxygen::tagDestinationDict[ref])) t << *dest << "/";
    t << "\" ";
  }
  else
  {
    t << "<a class=\"code\" ";
  }
  t << "href=\"";
  if (ref)
  {
    if ((dest=Doxygen::tagDestinationDict[ref])) t << relPath << *dest << "/";
  }
  else
  {
    t << relPath;
  }
  if (f) t << f << Doxygen::htmlFileExtension;
  if (anchor) t << "#" << anchor;
  t << "\"";
  if (tooltip) t << " title=\"" << convertToXML(tooltip) << "\"";
  t << ">";
  docify(name);
  t << "</a>";
  col+=strlen(name);
}

void HtmlGenerator::startTextLink(const char *f,const char *anchor)
{
  t << "<a href=\"";
  if (f)   t << relPath << f << Doxygen::htmlFileExtension;
  if (anchor) t << "#" << anchor;
  t << "\">"; 
}

void HtmlGenerator::endTextLink()
{
  t << "</a>";
}

void HtmlGenerator::startHtmlLink(const char *url)
{
  t << "<a ";
  if (usingTreeIndex()) t << "target=\"top\" ";
  t << "href=\"";
  if (url) t << url;
  t << "\">"; 
}

void HtmlGenerator::endHtmlLink()
{
  t << "</a>";
}

void HtmlGenerator::startGroupHeader()
{
  t << "<h2>";
}

void HtmlGenerator::endGroupHeader()
{
  t << "</h2>" << endl;
}

void HtmlGenerator::startSection(const char *lab,const char *,SectionInfo::SectionType type)
{
  switch(type)
  {
    case SectionInfo::Page:          t << "<h1>"; break;
    case SectionInfo::Section:       t << "<h2>"; break;
    case SectionInfo::Subsection:    t << "<h3>"; break;
    case SectionInfo::Subsubsection: t << "<h4>"; break;
    case SectionInfo::Paragraph:     t << "<h5>"; break;
    default: ASSERT(0); break;
  }
  t << "<a class=\"anchor\" name=\"" << lab << "\">";
}

void HtmlGenerator::endSection(const char *,SectionInfo::SectionType type)
{
  t << "</a>";
  switch(type)
  {
    case SectionInfo::Page:          t << "</h1>"; break;
    case SectionInfo::Section:       t << "</h2>"; break;
    case SectionInfo::Subsection:    t << "</h3>"; break;
    case SectionInfo::Subsubsection: t << "</h4>"; break;
    case SectionInfo::Paragraph:     t << "</h5>"; break;
    default: ASSERT(0); break;
  }
}

void HtmlGenerator::docify(const char *str)
{
  docify(str,FALSE);
}

void HtmlGenerator::docify(const char *str,bool inHtmlComment)
{
  if (str)
  {
    const char *p=str;
    char c;
    while (*p)
    {
      c=*p++;
      switch(c)
      {
        case '<':  t << "&lt;"; break;
        case '>':  t << "&gt;"; break;
        case '&':  t << "&amp;"; break;
        case '"':  t << "&quot;"; break;
        case '-':  if (inHtmlComment) t << "&#45;"; else t << "-"; break;
        case '\\':
                   if (*p=='<')
                     { t << "&lt;"; p++; }
                   else if (*p=='>')
                     { t << "&gt;"; p++; }
                   else
                     t << "\\";
                   break;
        default:   t << c; 
      }
    }
  }
}

void HtmlGenerator::codify(const char *str)
{
  //docify(str);
  //static char spaces[]="        ";
  if (str)
  { 
    const char *p=str;
    char c;
    int spacesToNextTabStop;
    while (*p)
    {
      c=*p++;
      switch(c)
      {
        case '\t': spacesToNextTabStop = 
                         Config_getInt("TAB_SIZE") - (col%Config_getInt("TAB_SIZE")); 
                   t << spaces.left(spacesToNextTabStop); 
                   col+=spacesToNextTabStop; 
                   break; 
        case '\n': t << "\n"; col=0; 
                   break;
        //case '\n': t << "<br>"; col=0; 
        //           break;
        case '\r': break;
        case '<':  t << "&lt;"; col++; 
                   break;
        case '>':  t << "&gt;"; col++; 
                   break;
        case '&':  t << "&amp;"; col++; 
                   break;
        //case ' ':  t << "&nbsp;"; col++;
        //           break;
        case '\\':
                   if (*p=='<')
                     { t << "&lt;"; p++; }
                   else if (*p=='>')
                     { t << "&gt;"; p++; }
                   else
                     t << "\\";
                   col++;
                   break;
        default:   t << c;    
                   col++;                    
                   break;
      }
    }
  }
}

void HtmlGenerator::writeChar(char c)
{
  char cs[2];
  cs[0]=c;
  cs[1]=0;
  docify(cs);
}

void HtmlGenerator::startClassDiagram()
{
  //t << "<p>";
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endClassDiagram(const ClassDiagram &d,
                                const char *fileName,const char *name)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  t << "\n<p><center><img src=\""
    << relPath << fileName << ".png\" usemap=\"#" << name << "_map\""
    << " border=\"0\" alt=\"\"></center>" << endl
    << "<map name=\"" << name << "_map\">" << endl;

  d.writeImage(t,dir,relPath,fileName);
  t << "</div>" << endl;
}


void HtmlGenerator::startMemberList()  
{ 
  DBG_HTML(t << "<!-- startMemberList -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
  }
  else
  {
    t << "<ul>" << endl; 
  }
}

void HtmlGenerator::endMemberList()    
{ 
  DBG_HTML(t << "<!-- endMemberList -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
  }
  else
  {
    t << "</ul>" << endl; 
  }
}

// annonymous type:
//  0 = single column right aligned
//  1 = double column left aligned
//  2 = single column left aligned
void HtmlGenerator::startMemberItem(int annoType) 
{ 
  DBG_HTML(t << "<!-- startMemberItem() -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "<tr>";
    switch(annoType)
    {
      case 0:  t << "<td class=\"memItemLeft\" nowrap align=\"right\" valign=\"top\">"; break;
      case 1:  t << "<td class=\"memItemLeft\" nowrap>"; break;
      case 2:  t << "<td class=\"memItemLeft\" nowrap valign=\"top\">"; break;
      default: t << "<td class=\"memTemplParams\" nowrap colspan=\"2\">"; break;
    }
  }
  else
  {
    t << "<li>"; 
  }
}

void HtmlGenerator::endMemberItem() 
{ 
  //DBG_HTML(t << "<!-- endMemberItem(" << (int)inGroup << "," << fileName << "," << headerName << " -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "</td></tr>\n"; 
  }
  t << endl; 
}

void HtmlGenerator::startMemberTemplateParams()
{
}

void HtmlGenerator::endMemberTemplateParams()
{
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "</td></tr>" << endl;
    t << "<tr><td class=\"memTemplItemLeft\" nowrap align=\"right\" valign=\"top\">";
  }
}


void HtmlGenerator::insertMemberAlign(bool templ) 
{ 
  DBG_HTML(t << "<!-- insertMemberAlign -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    QCString className = templ ? "memTemplItemRight" : "memItemRight";
    t << "&nbsp;</td><td class=\"" << className << "\" valign=\"bottom\">"; 
  }
}

void HtmlGenerator::startMemberDescription() 
{ 
  DBG_HTML(t << "<!-- startMemberDescription -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "<tr><td class=\"mdescLeft\">&nbsp;</td><td class=\"mdescRight\">"; 
  }
  else
  {
    t << "<dl class=\"el\"><dd class=\"mdescRight\">";
  }
}

void HtmlGenerator::endMemberDescription()   
{ 
  DBG_HTML(t << "<!-- endMemberDescription -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "<br></td></tr>" << endl; 
  }
  else
  {
    t << "<br></dl>";
  }
}

void HtmlGenerator::startMemberSections()
{
  DBG_HTML(t << "<!-- startMemberSections -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">" << endl;
    // HTML is not recursively decomposable, sorry
    t << "<tr><td></td></tr>" << endl;
  }
}

void HtmlGenerator::endMemberSections()
{
  DBG_HTML(t << "<!-- endMemberSections -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "</table>" << endl;
  }
}

void HtmlGenerator::startMemberHeader()
{
  DBG_HTML(t << "<!-- startMemberHeader -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "<tr><td colspan=\"2\"><br><h2>";
  }
  else
  {
    startGroupHeader();
  }
}

void HtmlGenerator::endMemberHeader()
{
  DBG_HTML(t << "<!-- endMemberHeader -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS"))
  {
    t << "</h2></td></tr>" << endl;
  }
  else
  {
    endGroupHeader();
  }
}

void HtmlGenerator::startMemberSubtitle()
{
  DBG_HTML(t << "<!-- startMemberSubtitle -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS")) t << "<tr><td colspan=\"2\">";
}

void HtmlGenerator::endMemberSubtitle()
{
  DBG_HTML(t << "<!-- endMemberSubtitle -->" << endl)
  if (Config_getBool("HTML_ALIGN_MEMBERS")) t << "<br><br></td></tr>" << endl;
}

void HtmlGenerator::startIndexList() 
{ 
  t << "<table>"  << endl; 
}

void HtmlGenerator::endIndexList()
{
  t << "</table>" << endl;
}

void HtmlGenerator::startIndexKey() 
{ 
  // inserted 'class = ...', 02 jan 2002, jh
  t << "  <tr><td class=\"indexkey\">"; 
}

void HtmlGenerator::endIndexKey()
{
  t << "</td>";
}

void HtmlGenerator::startIndexValue(bool) 
{ 
  // inserted 'class = ...', 02 jan 2002, jh
  t << "<td class=\"indexvalue\">"; 
}

void HtmlGenerator::endIndexValue(const char *,bool)
{
  t << "</td></tr>" << endl;
}

void HtmlGenerator::startMemberDocList()
{
  DBG_HTML(t << "<!-- startMemberDocList -->" << endl;)
  //t << "<table class=\"memlist\">" << endl;
  //t << "  <tr>" << endl;
  //t << "    <td>" << endl;
}

void HtmlGenerator::endMemberDocList()
{
  DBG_HTML(t << "<!-- endMemberDocList -->" << endl;)
  //t << "    </td>" << endl;
  //t << "  </tr>" << endl;
  //t << "</table>" << endl;
}

void HtmlGenerator::startMemberDoc(const char *,const char *,const char *,const char *) 
{ 
  DBG_HTML(t << "<!-- startMemberDoc -->" << endl;)
  //t << "<p>" << endl;
 
  t << "\n<div class=\"memitem\">" << endl;
  //t << "<table>" << endl;
  //t << "  <tr>" << endl;
  //t << "    <td>" << endl;
  //t << "      <table class=\"memproto\">" << endl;
  t << "<div class=\"memproto\">" << endl;
  
}

void HtmlGenerator::startMemberDocPrefixItem()
{
  DBG_HTML(t << "<!-- startMemberDocPrefixItem -->" << endl;)
  //t << "        <tr>" << endl;
  //t << "          <td class=\"memtemplate\" colspan=\"5\">";
  t << "<div class=\"memtemplate\">" << endl;
}

void HtmlGenerator::endMemberDocPrefixItem()
{
  DBG_HTML(t << "<!-- endMemberDocPrefixItem -->" << endl;)
  //t << "</td>" << endl;
  //t << "        </tr>" << endl;
  t << "</div>" << endl;
}

void HtmlGenerator::startMemberDocName(bool /*align*/)
{
  DBG_HTML(t << "<!-- startMemberDocName -->" << endl;)

  t << "      <table class=\"memname\">" << endl;
    
  t << "        <tr>" << endl;
  t << "          <td class=\"memname\">";
}

void HtmlGenerator::endMemberDocName()
{
  DBG_HTML(t << "<!-- endMemberDocName -->" << endl;)
  t << "          </td>" << endl;
}

void HtmlGenerator::startParameterList(bool openBracket)
{
  DBG_HTML(t << "<!-- startParameterList -->" << endl;)
  t << "          <td>";
  if (openBracket) t << "(";
  t << "</td>" << endl;
}

void HtmlGenerator::startParameterType(bool first,const char *key)
{
  if (first)
  {
    DBG_HTML(t << "<!-- startFirstParameterType -->" << endl;)
    t << "          <td class=\"paramtype\">";
  }
  else
  {
    DBG_HTML(t << "<!-- startParameterType -->" << endl;)
    t << "        <tr>" << endl;
    t << "          <td class=\"paramkey\">";
    if (key) t << key;
    t << "</td>" << endl;
    t << "          <td></td>" << endl;
    t << "          <td class=\"paramtype\">";
  }
}

void HtmlGenerator::endParameterType()
{
  DBG_HTML(t << "<!-- endParameterType -->" << endl;)
  t << "&nbsp;</td>" << endl;
}

void HtmlGenerator::startParameterName(bool /*oneArgOnly*/)
{
  DBG_HTML(t << "<!-- startParameterName -->" << endl;)
  t << "          <td class=\"paramname\">";
}

void HtmlGenerator::endParameterName(bool last,bool emptyList,bool closeBracket)
{
  DBG_HTML(t << "<!-- endParameterName -->" << endl;)
  if (last)
  {
    if (emptyList)
    {
      t << "          </td>" << endl;
      t << "          <td>";
      if (closeBracket) t << "&nbsp;)";
      t << "&nbsp;</td>" << endl;
      t << "          <td>";
    }
    else
    {
      t << "</td><td>&nbsp;</td>" << endl;
      t << "        </tr>" << endl;
      t << "        <tr>" << endl;
      t << "          <td></td>" << endl;
      t << "          <td>";
      if (closeBracket) t << ")";
      t << "</td>" << endl;
      t << "          <td></td><td></td><td>";
    }
  }
  else
  {
    t << "</td>" << endl;
    t << "        </tr>" << endl;
  }
}

void HtmlGenerator::endParameterList()
{
  DBG_HTML(t << "<!-- endParameterList -->" << endl;)
  t << "</td>" << endl;
  t << "        </tr>" << endl;
}

void HtmlGenerator::endMemberDoc(bool hasArgs)     
{ 
  DBG_HTML(t << "<!-- endMemberDoc -->" << endl;)
  if (!hasArgs)
  {
    t << "        </tr>" << endl;
  }
  t << "      </table>" << endl;
  //t << "    </td>" << endl;
  //t << "  </tr>" << endl;
  //t << "</table>" << endl;
  t << "</div>" << endl;
}

void HtmlGenerator::startDotGraph()
{
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endDotGraph(const DotClassGraph &g)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  g.writeGraph(t,BITMAP,dir,relPath);
  if (Config_getBool("GENERATE_LEGEND"))
  {
    t << "<center><font size=\"2\">[";
    startHtmlLink(relPath+"graph_legend"+Doxygen::htmlFileExtension);
    t << theTranslator->trLegend();
    endHtmlLink();
    t << "]</font></center>";
  }
  t << "</div>" << endl;
}

void HtmlGenerator::startInclDepGraph()
{
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endInclDepGraph(const DotInclDepGraph &g)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  g.writeGraph(t,BITMAP,dir,relPath);
  t << "</div>" << endl;
}

void HtmlGenerator::startGroupCollaboration()
{
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endGroupCollaboration(const DotGroupCollaboration &g)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  g.writeGraph(t,BITMAP,dir,relPath);
  t << "</div>" << endl;
}

void HtmlGenerator::startCallGraph()
{
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endCallGraph(const DotCallGraph &g)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  g.writeGraph(t,BITMAP,dir,relPath);
  t << "</div>" << endl;
}

void HtmlGenerator::startDirDepGraph()
{
  t << "<div class=\"dynheader\">" << endl;
}

void HtmlGenerator::endDirDepGraph(const DotDirDeps &g)
{
  t << "</div>" << endl;
  t << "<div class=\"dynsection\">" << endl;
  g.writeGraph(t,BITMAP,dir,relPath);
  t << "</div>" << endl;
}

void HtmlGenerator::writeGraphicalHierarchy(const DotGfxHierarchyTable &g)
{
  g.writeGraph(t,dir);
}

void HtmlGenerator::startMemberGroupHeader(bool)
{
  t << "<tr><td colspan=\"2\"><div class=\"groupHeader\">";
}

void HtmlGenerator::endMemberGroupHeader()
{
  t << "</div></td></tr>" << endl;
}

void HtmlGenerator::startMemberGroupDocs()
{
  t << "<tr><td colspan=\"2\"><div class=\"groupText\">";
}

void HtmlGenerator::endMemberGroupDocs()
{
  t << "<br><br></div></td></tr>" << endl;
}

void HtmlGenerator::startMemberGroup()
{
}

void HtmlGenerator::endMemberGroup(bool)
{
}

void HtmlGenerator::startIndent()        
{ 
  DBG_HTML(t << "<!-- startIndent -->" << endl;)

  t << "<div class=\"memdoc\">\n";
}

void HtmlGenerator::endIndent()          
{ 
  DBG_HTML(t << "<!-- endIndent -->" << endl;)
  t << endl << "</div>" << endl << "</div><p>" << endl; 
}

void HtmlGenerator::addIndexItem(const char *,const char *)
{
}

void HtmlGenerator::writeNonBreakableSpace(int n)
{
  int i;
  for (i=0;i<n;i++)
  {
    t << "&nbsp;";
  }
}

void HtmlGenerator::writeLineNumber(const char *ref,const char *filename,
                                    const char *anchor,int l)
{
  QCString lineNumber,lineAnchor;
  lineNumber.sprintf("%05d",l);
  lineAnchor.sprintf("l%05d",l);

  if (filename)
  {
    startCodeAnchor(lineAnchor);
    writeCodeLink(ref,filename,anchor,lineNumber,0);
    endCodeAnchor();
  }
  else
  {
    startCodeAnchor(lineAnchor);
    codify(lineNumber);
    endCodeAnchor();
  }
  codify(" ");
}

void HtmlGenerator::startSimpleSect(SectionTypes,
                                const char *filename,const char *anchor,
                                const char *title)
{
  t << "<dl compact><dt><b>";
  if (filename)
  {
    writeObjectLink(0,filename,anchor,title);
  }
  else
  {
    docify(title);
  }
  t << "</b></dt>";
}

void HtmlGenerator::endSimpleSect()
{
  t << "</dl>"; 
}

void HtmlGenerator::startParamList(ParamListTypes,
                                const char *title)
{
  t << "<dl compact><dt><b>";
  docify(title);
  t << "</b></dt>";
}

void HtmlGenerator::endParamList()
{
  t << "</dl>"; 
}

void HtmlGenerator::printDoc(DocNode *n,const char *langExt)
{
  HtmlDocVisitor *visitor = new HtmlDocVisitor(t,*this,langExt);
  n->accept(visitor);
  delete visitor; 
}

//---------------- helpers for index generation -----------------------------

static void startQuickIndexList(QTextStream &t,bool compact)
{
  if (compact) 
  {
    t << "  <div class=\"tabs\">\n";
    t << "    <ul>\n"; 
  }
  else 
  {
    t << "<ul>";
  }
}

static void endQuickIndexList(QTextStream &t,bool compact)
{
  if (compact) 
  {
    t << "    </ul>\n";
    t << "  </div>\n";
  }
  else 
  {
    t << "</ul>\n";
  }
}

static void startQuickIndexItem(QTextStream &t,const char *l,
                                bool hl,bool /*compact*/,
                                const QCString &relPath)
{
  t << "      <li"; if (hl) t << " class=\"current\"";
  t << "><a ";
  t << "href=\"" << relPath << l << "\">";
  t << "<span>";
}

static void endQuickIndexItem(QTextStream &t)
{
  t << "</span>";
  t << "</a>";
  t << "</li>\n";
}

static QCString fixSpaces(const QCString &s)
{
  return substitute(s," ","&nbsp;");
}

#define NEW_LAYOUT
#ifdef NEW_LAYOUT

static bool quickLinkVisible(LayoutNavEntry::Kind kind)
{
  switch (kind)
  {
    case LayoutNavEntry::MainPage:         return TRUE; 
    case LayoutNavEntry::Pages:            return indexedPages>0;
    case LayoutNavEntry::Modules:          return documentedGroups>0;
    case LayoutNavEntry::Namespaces:       return documentedNamespaces>0;
    case LayoutNavEntry::NamespaceMembers: return documentedNamespaceMembers[NMHL_All]>0;
    case LayoutNavEntry::Classes:          return annotatedClasses>0;
    case LayoutNavEntry::ClassAnnotated:   return annotatedClasses>0; 
    case LayoutNavEntry::ClassHierarchy:   return hierarchyClasses>0;
    case LayoutNavEntry::ClassMembers:     return documentedClassMembers[CMHL_All]>0;
    case LayoutNavEntry::Files:            return documentedHtmlFiles>0;
    case LayoutNavEntry::FileGlobals:      return documentedFileMembers[FMHL_All]>0;
    case LayoutNavEntry::Dirs:             return documentedDirs>0;
    case LayoutNavEntry::Examples:         return Doxygen::exampleSDict->count()>0;
  }
  return FALSE;
}

static void renderQuickLinksAsTree(QTextStream &t,const QCString &relPath,LayoutNavEntry *root)

{
  QListIterator<LayoutNavEntry> li(root->children());
  LayoutNavEntry *entry;
  int count=0;
  for (li.toFirst();(entry=li.current());++li)
  {
    if (entry->visible() && quickLinkVisible(entry->kind())) count++;
  }
  if (count>0) // at least one item is visible
  {
    startQuickIndexList(t,FALSE);
    for (li.toFirst();(entry=li.current());++li)
    {
      if (entry->visible() && quickLinkVisible(entry->kind()))
      {
        startQuickIndexItem(t,entry->baseFile()+Doxygen::htmlFileExtension,
                            FALSE,FALSE,relPath);
        t << fixSpaces(entry->title());
        endQuickIndexItem(t);
        // recursive into child list
        renderQuickLinksAsTree(t,relPath,entry);
      }
    }
    endQuickIndexList(t,FALSE);
  }
}


static void renderQuickLinksAsTabs(QTextStream &t,const QCString &relPath,
                             LayoutNavEntry *hlEntry,LayoutNavEntry::Kind kind,
                             bool highlightParent,bool highlightSearch)
{
  if (hlEntry->parent()) // first draw the tabs for the parent of hlEntry
  {
    renderQuickLinksAsTabs(t,relPath,hlEntry->parent(),kind,highlightParent,highlightSearch);
  }
  if (hlEntry->parent() && hlEntry->parent()->children().count()>0) // draw tabs for row containing hlEntry
  {
    QListIterator<LayoutNavEntry> li(hlEntry->parent()->children());
    LayoutNavEntry *entry;

    int count=0;
    for (li.toFirst();(entry=li.current());++li)
    {
      if (entry->visible() && quickLinkVisible(entry->kind())) count++;
    }
    if (count>0) // at least one item is visible
    {
      startQuickIndexList(t,TRUE);
      for (li.toFirst();(entry=li.current());++li)
      {
        if (entry->visible() && quickLinkVisible(entry->kind()))
        {
          startQuickIndexItem(t,entry->baseFile()+Doxygen::htmlFileExtension,
              entry==hlEntry  && (entry->children().count()>0 || (entry->kind()==kind && !highlightParent)),
              TRUE,relPath);
          t << fixSpaces(entry->title());
          endQuickIndexItem(t);
        }
      }
      if (hlEntry->parent()==LayoutDocManager::instance().rootNavEntry())
      {
        // last item of the top row -> special case for search engine
        if (Config_getBool("SEARCHENGINE"))
        {
          QCString searchFor = fixSpaces(theTranslator->trSearchForIndex());
          if (searchFor.at(0)=='S') searchFor="<u>S</u>"+searchFor.mid(1);
          t << "    <li>\n";
          t << "      <form action=\"" << relPath << "search.php\" method=\"get\">\n";
          t << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n";
          t << "          <tr>\n";
          t << "            <td><label>&nbsp;" << searchFor << "&nbsp;</label></td>\n";
          if (!highlightSearch)
          {
            t << "            <td><input type=\"text\" name=\"query\" value=\"\" size=\"20\" accesskey=\"s\"/></td>\n";
            t << "          </tr>\n";
            t << "        </table>\n";
            t << "      </form>\n";
            t << "    </li>\n";
          }
        } 
        if (!highlightSearch) // on the search page the page will be ended by the
                              // page itself
        {
          endQuickIndexList(t,TRUE);
        }
      }
      else // normal case
      {
        endQuickIndexList(t,TRUE);
      }
    }
  }
}

static void writeDefaultQuickLinks(QTextStream &t,bool compact,
                                   HighlightedItem hli,const QCString &relPath)
{
  LayoutNavEntry *root = LayoutDocManager::instance().rootNavEntry();
  LayoutNavEntry::Kind kind = (LayoutNavEntry::Kind)-1;
  bool highlightParent=FALSE;
  switch (hli) // map HLI enums to LayoutNavEntry::Kind enums
  {
    case HLI_Main:             kind = LayoutNavEntry::MainPage;         break;
    case HLI_Modules:          kind = LayoutNavEntry::Modules;          break;
    case HLI_Directories:      kind = LayoutNavEntry::Dirs;             break;
    case HLI_Namespaces:       kind = LayoutNavEntry::Namespaces;       break;
    case HLI_Hierarchy:        kind = LayoutNavEntry::ClassHierarchy;   break;
    case HLI_Classes:          kind = LayoutNavEntry::Classes;          break;
    case HLI_Annotated:        kind = LayoutNavEntry::ClassAnnotated;   break;
    case HLI_Files:            kind = LayoutNavEntry::Files;            break;
    case HLI_NamespaceMembers: kind = LayoutNavEntry::NamespaceMembers; break;
    case HLI_Functions:        kind = LayoutNavEntry::ClassMembers;     break;
    case HLI_Globals:          kind = LayoutNavEntry::FileGlobals;      break;
    case HLI_Pages:            kind = LayoutNavEntry::Pages;            break;
    case HLI_Examples:         kind = LayoutNavEntry::Examples;         break;
    case HLI_ClassVisible:     kind = LayoutNavEntry::Classes;    highlightParent = TRUE; break;
    case HLI_NamespaceVisible: kind = LayoutNavEntry::Namespaces; highlightParent = TRUE; break;
    case HLI_FileVisible:      kind = LayoutNavEntry::Files;      highlightParent = TRUE; break;
    case HLI_None:   break;
    case HLI_Search: break;
  }
  
  if (compact)
  {
    // find highlighted index item
    LayoutNavEntry *hlEntry = root->find(kind);
    if (!hlEntry) // highlighted item not found in the index! -> just show the level 1 index...
    {
      highlightParent=TRUE;
      hlEntry = root->children().getFirst();
      if (hlEntry==0) 
      {
        return; // argl, empty index!
      }
    }
    renderQuickLinksAsTabs(t,relPath,hlEntry,kind,highlightParent,hli==HLI_Search);
  }
  else
  {
    renderQuickLinksAsTree(t,relPath,root);
  }
}

#else // old fixed layout

static void writeNamespaceSubIndex(QTextStream &t,bool compact,
                                  HighlightedItem hli,const QCString &relPath
                                 )
{
  bool fortranOpt = Config_getBool("OPTIMIZE_FOR_FORTRAN");
  startQuickIndexList(t,compact);
  if (documentedNamespaces>0)
  {
    startQuickIndexItem(t,"namespaces"+Doxygen::htmlFileExtension,
        hli==HLI_Namespaces,compact,relPath);
    if (Config_getBool("OPTIMIZE_OUTPUT_JAVA"))
    {
      t << fixSpaces(theTranslator->trPackages());
    }
    else if(fortranOpt)
    {
      t << theTranslator->trModulesList();
    }
      else
    {
      t << theTranslator->trNamespaceList();
    }
    endQuickIndexItem(t);
  }
  if (documentedNamespaceMembers[NMHL_All]>0)
  {
    startQuickIndexItem(t,"namespacemembers"+Doxygen::htmlFileExtension,
        hli==HLI_NamespaceMembers,compact,relPath);
    if (Config_getBool("OPTIMIZE_OUTPUT_JAVA"))
    {
      t << fixSpaces(theTranslator->trPackageMembers());
    }
    else if(fortranOpt)
    {
      t << fixSpaces(theTranslator->trModulesMembers());
    }
      else
    {
      t << fixSpaces(theTranslator->trNamespaceMembers());
    }
    endQuickIndexItem(t);
  }
  endQuickIndexList(t,compact);
}

static void writeClassSubIndex(QTextStream &t,bool compact,
                               HighlightedItem hli,const QCString &relPath
                              )
{
  bool fortranOpt=Config_getBool("OPTIMIZE_FOR_FORTRAN");
  bool vhdlOpt=Config_getBool("OPTIMIZE_OUTPUT_VHDL");
  startQuickIndexList(t,compact);
  if (annotatedClasses>0)
  {
    if (Config_getBool("ALPHABETICAL_INDEX"))
    {
      startQuickIndexItem(t,"classes"+Doxygen::htmlFileExtension,
          hli==HLI_Classes,compact,relPath);
      t << fixSpaces(theTranslator->trAlphabeticalList());
      endQuickIndexItem(t);
    }
    startQuickIndexItem(t,"annotated"+Doxygen::htmlFileExtension,
        hli==HLI_Annotated,compact,relPath);
      if (fortranOpt)
      {
        t << fixSpaces(theTranslator->trCompoundListFortran());
      }
      else if (vhdlOpt)
      {
        t << fixSpaces(VhdlDocGen::trDesignUnitList());
      }
      else
      {
        t << fixSpaces(theTranslator->trCompoundList());
      }
    
    endQuickIndexItem(t);
  } 
  if (hierarchyClasses>0)
  {
    QCString title = theTranslator->trClassHierarchy();
    if (vhdlOpt) title = VhdlDocGen::trDesignUnitHierarchy();
    startQuickIndexItem(t,"hierarchy"+Doxygen::htmlFileExtension,
        hli==HLI_Hierarchy,compact,relPath);
    t << fixSpaces(title);
    endQuickIndexItem(t);
  } 
  if (documentedClassMembers[CMHL_All]>0)
  {
    startQuickIndexItem(t,"functions"+Doxygen::htmlFileExtension,
        hli==HLI_Functions,compact,relPath);
    if (fortranOpt)
    {
      t << fixSpaces(theTranslator->trCompoundMembersFortran());
    }
    else if (vhdlOpt)
    {
      t << fixSpaces(VhdlDocGen::trDesignUnitMembers());
    }
    else
    {
      t << fixSpaces(theTranslator->trCompoundMembers());
    }
    endQuickIndexItem(t);
  } 
  endQuickIndexList(t,compact);
}

static void writeFileSubIndex(QTextStream &t,bool compact,
                              HighlightedItem hli,const QCString &relPath)
{
  startQuickIndexList(t,compact);
  if (documentedHtmlFiles>0)
  {
    startQuickIndexItem(t,"files"+Doxygen::htmlFileExtension,
        hli==HLI_Files,compact,relPath);
    t << fixSpaces(theTranslator->trFileList());
    endQuickIndexItem(t);
  } 
  if (documentedFileMembers[FMHL_All]>0)
  {
    startQuickIndexItem(t,"globals"+Doxygen::htmlFileExtension,
        hli==HLI_Globals,compact,relPath);
    t << fixSpaces(theTranslator->trFileMembers());
    endQuickIndexItem(t);
  } 
  endQuickIndexList(t,compact);
}

static void writeDefaultQuickLinks(QTextStream &t,bool compact,
                                   HighlightedItem hli,const QCString &relPath)
{
  bool fortranOpt = Config_getBool("OPTIMIZE_FOR_FORTRAN");
  bool vhdlOpt    = Config_getBool("OPTIMIZE_OUTPUT_VHDL");
  startQuickIndexList(t,compact);

  if (usingTreeIndex())
  {
    startQuickIndexItem(t,"main"+Doxygen::htmlFileExtension,
                        hli==HLI_Main,compact,relPath);
  }
  else
  {
    startQuickIndexItem(t,"index"+Doxygen::htmlFileExtension,
                        hli==HLI_Main,compact,relPath);
  }
  t << fixSpaces(theTranslator->trMainPage());
  endQuickIndexItem(t);

  // -------------- Related pages
  
  if (indexedPages>0)
  {
    startQuickIndexItem(t,"pages"+Doxygen::htmlFileExtension,
                        hli==HLI_Pages,compact,relPath);
    t << fixSpaces(theTranslator->trRelatedPages());
    endQuickIndexItem(t);
  } 

  // --------------- Modules

  if (documentedGroups>0)
  {
    startQuickIndexItem(t,"modules"+Doxygen::htmlFileExtension,
                        hli==HLI_Modules,compact,relPath);
    t << fixSpaces(theTranslator->trModules());
    endQuickIndexItem(t);
  } 

  // --------------- Namespace indices

  if (documentedNamespaces>0)
  {
    startQuickIndexItem(t,"namespaces"+Doxygen::htmlFileExtension,
        hli==HLI_Namespaces || hli==HLI_NamespaceMembers || hli==HLI_NamespaceVisible,
        compact,relPath);
    if (Config_getBool("OPTIMIZE_OUTPUT_JAVA"))
    {
      t << fixSpaces(theTranslator->trPackages());
    }
    else if (fortranOpt)
    {
      t << theTranslator->trModules();
    }
    else
    {
      t << theTranslator->trNamespaces();
    }
    endQuickIndexItem(t);
    if (!compact)
    {
      writeNamespaceSubIndex(t,compact,hli,relPath);
    }
  }


  // -------------- Class indices

  if (annotatedClasses>0)
  {
    static bool alphaIndex=Config_getBool("ALPHABETICAL_INDEX");
    {
      startQuickIndexItem(t,QCString(alphaIndex?"classes":"annotated")+Doxygen::htmlFileExtension,
          hli==HLI_Hierarchy || hli==HLI_Classes || 
          hli==HLI_Annotated || hli==HLI_Functions || hli==HLI_ClassVisible,
          compact,relPath);
    }
    if (fortranOpt)
    {
      t << fixSpaces(theTranslator->trDataTypes());
    }
    else if (vhdlOpt)
    {
      t << fixSpaces(VhdlDocGen::trDesignUnits());
    }
    else
    {
      t << fixSpaces(theTranslator->trClasses());
    }
    endQuickIndexItem(t);
    if (!compact)
    {
      writeClassSubIndex(t,compact,hli,relPath);
    }
  }

  // -------------- File

  if (documentedHtmlFiles>0)
  {
    startQuickIndexItem(t,"files"+Doxygen::htmlFileExtension,
                        hli==HLI_Files || hli==HLI_Globals || hli==HLI_FileVisible,
                        compact,relPath);
    t << fixSpaces(theTranslator->trFile(TRUE,FALSE));
    endQuickIndexItem(t);
    if (!compact)
    {
      writeFileSubIndex(t,compact,hli,relPath);
    }
  } 

  // -------------- Directories
  
  if (Config_getBool("SHOW_DIRECTORIES") && documentedDirs>0)
  {
    startQuickIndexItem(t,"dirs"+Doxygen::htmlFileExtension,
                        hli==HLI_Directories,compact,relPath);
    t << fixSpaces(theTranslator->trDirectories());
    endQuickIndexItem(t);
  } 

  // -------------- Examples
  
  if (Doxygen::exampleSDict->count()>0)
  {
    startQuickIndexItem(t,"examples"+Doxygen::htmlFileExtension,
                        hli==HLI_Examples,compact,relPath);
    t << fixSpaces(theTranslator->trExamples());
    endQuickIndexItem(t);
  } 

  // -------------- Search field

  if (Config_getBool("SEARCHENGINE"))
  {
    QCString searchFor = fixSpaces(theTranslator->trSearchForIndex());
    if (searchFor.at(0)=='S') searchFor="<u>S</u>"+searchFor.mid(1);
    t << "    <li>\n";
    t << "      <form action=\"" << relPath << "search.php\" method=\"get\">\n";
    t << "        <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">\n";
    t << "          <tr>\n";
    t << "            <td><label>&nbsp;" << searchFor << "&nbsp;</label></td>\n";
    if (hli!=HLI_Search)
    {
      t << "            <td><input type=\"text\" name=\"query\" value=\"\" size=\"20\" accesskey=\"s\"/></td>\n";
      t << "          </tr>\n";
      t << "        </table>\n";
      t << "      </form>\n";
      t << "    </li>\n";
    }
  } 
  if (hli!=HLI_Search) // on the search page the page will be ended by the
                       // page itself
  {
    endQuickIndexList(t,compact);
  }

  //-------------------------------------------------------------------------
  // write sub indices in compact mode

  if ((hli==HLI_Namespaces || hli==HLI_NamespaceMembers || 
       hli==HLI_NamespaceVisible
      ) && 
      documentedNamespaces>0 &&
      documentedNamespaceMembers[NMHL_All]>0)
  {
    writeNamespaceSubIndex(t,compact,hli,relPath);
  }
  else if ((hli==HLI_Hierarchy || hli==HLI_Classes || 
            hli==HLI_Annotated || hli==HLI_Functions || 
            hli==HLI_ClassVisible || !compact
           ) && annotatedClasses>0
          )
  {
    writeClassSubIndex(t,compact,hli,relPath);
  }
  else if ((hli==HLI_Files || hli==HLI_Globals || 
            hli==HLI_FileVisible || !compact
           ) && documentedHtmlFiles>0 && documentedFileMembers[FMHL_All]>0
          )
  {
    writeFileSubIndex(t,compact,hli,relPath);
  }
  
}
#endif

void HtmlGenerator::startQuickIndices()
{
  if (!Config_getBool("DISABLE_INDEX"))
  {
    t << "<div class=\"navigation\" id=\"top\">" << endl;
  }
}

void HtmlGenerator::endQuickIndices()
{
  if (!Config_getBool("DISABLE_INDEX"))
  {
    t << "</div>" << endl;
  }
}

void HtmlGenerator::startContents()
{
  t << "<div class=\"contents\">" << endl;
}

void HtmlGenerator::endContents()
{
  t << "</div>" << endl;
}

void HtmlGenerator::writeQuickLinks(bool compact,HighlightedItem hli)
{
  writeDefaultQuickLinks(t,compact,hli,relPath);
}

void HtmlGenerator::writeSearchPage()
{
  if (Config_getBool("SEARCHENGINE") && Config_getBool("GENERATE_HTML"))
  {
    QCString fileName = Config_getString("HTML_OUTPUT")+"/search.php";
    QFile f(fileName);
    if (f.open(IO_WriteOnly))
    {
      QTextStream t(&f);
      t.setEncoding(QTextStream::UnicodeUTF8);
      if (g_header.isEmpty()) 
      {
        writeDefaultHeaderFile(t,theTranslator->trSearch().data(),0,FALSE);
      }
      else
      {
        t << substituteKeywords(g_header,"Search","");
      }
      t << "<!-- " << theTranslator->trGeneratedBy() << " Doxygen " 
        << versionString << " -->" << endl;
      if (!Config_getBool("DISABLE_INDEX")) 
      { 
        writeDefaultQuickLinks(t,TRUE,HLI_Search,"");
      }
      else
      {
        t << "&nbsp;\n<div class=\"qindex\">\n";
        t << "  <form class=\"search\" action=\"search.php\" "
          << "method=\"get\">\n";
      }

      t << "\n<?php\n\n";
      t << "function search_results()\n";
      t << "{\n";
      t << "  return \"" << theTranslator->trSearchResultsTitle() << "\";\n";
      t << "}\n";
      t << "\n";
      t << "function matches_text($num)\n";
      t << "{\n";
      t << "  if ($num==0)\n";
      t << "  {\n";
      t << "    return \"" << theTranslator->trSearchResults(0) << "\";\n";
      t << "  }\n";
      t << "  else if ($num==1)\n";
      t << "  {\n";
      t << "    return \"" << theTranslator->trSearchResults(1) << "\";\n";
      t << "  }\n";
      t << "  else // $num>1\n";
      t << "  {\n";
      t << "    return \"" << theTranslator->trSearchResults(2) << "\";\n";
      t << "  }\n";
      t << "}\n";
      t << "\n";
      t << "function report_matches()\n";
      t << "{\n";
      t << "  return \"" << theTranslator->trSearchMatches() << " \";\n";
      t << "}\n";
      t << "function end_form($value)\n";
      t << "{\n";
      t << "  echo \"" 
        << "            <td><input type=\\\"text\\\" name=\\\"query\\\" value=\\\"$value\\\" size=\\\"20\\\" accesskey=\\\"s\\\"/></td>\\n"
        << "          </tr>\\n"
        << "        </table>\\n"
        << "      </form>\\n"
        << "    </li>\\n"
        << "  </ul>\\n"
        << "</div>\\n"
        << "\";\n";
      t << "}\n";
      t << "\n";
      t << search_script;
      t << "\n";
      t << "?>\n";
      writePageFooter(t,"Search","");
    }
  }
}

void HtmlGenerator::generateSectionImages()
{
  {
    QCString fileName = Config_getString("HTML_OUTPUT")+"/open.gif";
    QFile f(fileName);
    if (f.open(IO_WriteOnly))
    {
      f.writeBlock((char*)open_gif,open_gif_len);
    }
  }
  {
    QCString fileName = Config_getString("HTML_OUTPUT")+"/closed.gif";
    QFile f(fileName);
    if (f.open(IO_WriteOnly))
    {
      f.writeBlock((char*)closed_gif,closed_gif_len);
    }
  }
}

void HtmlGenerator::startConstraintList(const char *header)
{
  t << "<div class=\"typeconstraint\">" << endl;
  t << "<dl compact><dt><b>" << header << "</b><dt><dd>" << endl;
  t << "<table border=\"0\" cellspacing=\"2\" cellpadding=\"0\">" << endl;
}

void HtmlGenerator::startConstraintParam()
{
  t << "<tr><td valign=\"top\"><em>";
}

void HtmlGenerator::endConstraintParam()
{
  t << "</em></td>";
}

void HtmlGenerator::startConstraintType()
{
  t << "<td>&nbsp;:</td><td valign=\"top\"><em>";
}

void HtmlGenerator::endConstraintType()
{
  t << "</em></td>";
}

void HtmlGenerator::startConstraintDocs()
{
  t << "<td>&nbsp;";
}

void HtmlGenerator::endConstraintDocs()
{
  t << "</td></tr>" << endl;
}

void HtmlGenerator::endConstraintList()
{
  t << "</table>" << endl;
  t << "</dl>" << endl;
  t << "</div>" << endl;
}


