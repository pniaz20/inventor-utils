/*
 * Copyright 1996, Portable Graphics, Inc., Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * IRIS GL and OpenGL are registered trademarks, and Inventor and
 * Open Inventor are trademarks of Silicon Graphics, Inc.
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Portable Graphics, Inc.,
 * 3006 Longhorn Blvd. Suite #105,  Austin, TX 78758-7631.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF PORTABLE GRAPHICS, INC. AND SILICON GRAPHICS, INC. ANY
 * DUPLICATION, MODIFICATION, DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN
 * WHOLE, OR IN PART, IS STRICTLY PROHIBITED WITHOUT THE PRIOR EXPRESS
 * WRITTEN  PERMISSION OF PORTABLE GRAPHICS, INC.
 */


const char box[] = {
0x23,0x49,0x6e,0x76,0x65,0x6e,0x74,0x6f,0x72,0x20,0x56,0x32,0x2e,0x30,0x20,0x62,0x69,0x6e,0x61,0x72,0x79,0x20,0x20,0xa,0x0,0x0,0x0,0x9,0x53,0x65,0x70,0x61,0x72,0x61,0x74,0x6f,0x72,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x6,0x0,0x0,0x0,0xb,0x43,0x6f,0x6f,0x72,0x64,0x69,0x6e,0x61,0x74,0x65,0x33,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x5,0x70,0x6f,0x69,0x6e,0x74,0x0,0x0,0x0,0x0,0x0,0x0,0x18,0xc0,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xc8,0x0,0x0,0x40,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xc8,0x0,0x0,0x40,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xc8,0x0,0x0,0xc0,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xc8,0x0,0x0,0xc0,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xb8,0x0,0x0,0x40,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xb8,0x0,0x0,0x40,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0xc8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xb8,0x0,0x0,0x40,0xb8,0x0,0x0,0xc0,0x40,0x0,0x0,0x40,0xb8,0x0,0x0,0x40,0xb8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0x40,0x0,0x0,0xc0,0xb8,0x0,0x0,0xc0,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xc8,0x0,0x0,0x40,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xc8,0x0,0x0,0x40,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xc8,0x0,0x0,0xc0,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xc8,0x0,0x0,0xc0,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xb8,0x0,0x0,0x40,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xb8,0x0,0x0,0x40,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xb8,0x0,0x0,0xc0,0xc8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xb8,0x0,0x0,0xc0,0xb8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xb8,0x0,0x0,0x40,0xb8,0x0,0x0,0x3f,0x19,0x99,0x9a,0x40,0xb8,0x0,0x0,0x40,0xb8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xb8,0x0,0x0,0xc0,0xb8,0x0,0x0,0x3f,0x19,0x99,0x9a,0xc0,0xb8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x6,0x4e,0x6f,0x72,0x6d,0x61,0x6c,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x6,0x76,0x65,0x63,0x74,0x6f,0x72,0x0,0x0,0x0,0x0,0x0,0x6,0x0,0x0,0x0,0x0,0xbf,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3f,0x80,0x0,0x0,0x3f,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xbf,0x80,0x0,0x0,0xbf,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xd,0x4e,0x6f,0x72,0x6d,0x61,0x6c,0x42,0x69,0x6e,0x64,0x69,0x6e,0x67,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x5,0x76,0x61,0x6c,0x75,0x65,0x0,0x0,0x0,0x0,0x0,0x0,0x10,0x50,0x45,0x52,0x5f,0x46,0x41,0x43,0x45,0x5f,0x49,0x4e,0x44,0x45,0x58,0x45,0x44,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0xc,0x64,0x69,0x66,0x66,0x75,0x73,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x0,0x0,0x0,0x1,0x3f,0x19,0x99,0x9a,0x3e,0xcc,0xcc,0xcd,0x3d,0xa3,0xd7,0xa,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf,0x4d,0x61,0x74,0x65,0x72,0x69,0x61,0x6c,0x42,0x69,0x6e,0x64,0x69,0x6e,0x67,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x5,0x76,0x61,0x6c,0x75,0x65,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0x4f,0x56,0x45,0x52,0x41,0x4c,0x4c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xe,0x49,0x6e,0x64,0x65,0x78,0x65,0x64,0x46,0x61,0x63,0x65,0x53,0x65,0x74,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0xa,0x63,0x6f,0x6f,0x72,0x64,0x49,0x6e,0x64,0x65,0x78,0x0,0x0,0x0,0x0,0x0,0x41,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0xd,0x0,0x0,0x0,0xc,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0xd,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0xf,0x0,0x0,0x0,0xe,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0xc,0x0,0x0,0x0,0xd,0x0,0x0,0x0,0x11,0x0,0x0,0x0,0x10,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x11,0x0,0x0,0x0,0x12,0x0,0x0,0x0,0x16,0x0,0x0,0x0,0x15,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x12,0x0,0x0,0x0,0xe,0x0,0x0,0x0,0xf,0x0,0x0,0x0,0x13,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x13,0x0,0x0,0x0,0x10,0x0,0x0,0x0,0x14,0x0,0x0,0x0,0x17,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x14,0x0,0x0,0x0,0x15,0x0,0x0,0x0,0x5,0x0,0x0,0x0,0x4,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x15,0x0,0x0,0x0,0x16,0x0,0x0,0x0,0x6,0x0,0x0,0x0,0x5,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x16,0x0,0x0,0x0,0x17,0x0,0x0,0x0,0x7,0x0,0x0,0x0,0x6,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x17,0x0,0x0,0x0,0x14,0x0,0x0,0x0,0x4,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xb,0x6e,0x6f,0x72,0x6d,0x61,0x6c,0x49,0x6e,0x64,0x65,0x78,0x0,0x0,0x0,0x0,0xd,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x4,0x0,0x0,0x0,0x5,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x4,0x0,0x0,0x0,0x5,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x3,0x0,0x0,0x0,0x0
};
