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


#ifndef PLAYCLASS_H
#define PLAYCLASS_H

#include <audio.h>
#include <audiofile.h>

class PlayClass;

typedef void PlayClassCB(void *data, PlayClass *pc);

class PlayClass {

  private:
    int   init_audio(AFfilehandle, ALport *, ALconfig *);
    int   play_audio_samps(AFfilehandle , ALport, ALconfig);
    static void  go(void *);

    int  audio_pid;
    int  caught_sigint;
    long filefmt;         /* input file format */
    int  fd;		  /* input file descriptor */
    char *myname;	  /* name of this program */
    int verbose, rude, quiet; /* global flags */
    int bytes_per_samp;	  /* sample width */
    long bits_per_samp;         /* sample resolution */
    int samps_per_frame;	  /* frame size */
    int frames_per_sec;	  /* sample rate */
    int bytes_per_buf;      	  /* bytes per sample buffer */
    int samps_per_buf;      	  /* samples per sample buffer */
    int frames_per_buf;     	  /* frames per sample buffer */
    double secs_per_frame;     /* time it takes to play one audio frame */
    double secs_per_buf;       /* time it takes to play one sample buffer */
    char *sampbuf;          	  /* the sample buffer */
    long compression;          /* audio data compression type */
    double file_rate;          /* audio file sample rate */
    char  *filename;
    PlayClassCB  *doneCallback;
    void         *userData;
    short sproced;

//    ALconfig audio_port_config;

    void attenuatesamps(void *, long, long, double, double,
			double *, double, int);
    short loop;
    short fading_in;	  /* while fading in */
    short fading_out;	  /* while fading out */
    double in_time;	  /* fade in time, sec */
    double play_time;	  /* play time, sec */
    double out_time;	  /* fade out time, sec */
    double fade_level;	  /* current fade_level */
    double max_level;	  /* maximum output level */
    short timed;
    short isLive;  /* is the child process still alive? */
    short isDone; /* are we done playing the audio */

  public:
    PlayClass(char *);
    ~PlayClass();
    int   beginPlaying(); // begin playing but do not sproc
    void setFilename(char *); // set the audio file name
    void setVerbose(int); // print out what is happening
    void setQuiet(int); // do not print out everything
    void setRude(int); // change the hardware sampling rate
    void setCallback(PlayClassCB *, void *);
    int start(); // play the file
    void fadeOut(); // fade out the audio using the fade out time
                    // THIS DOES NOT KILL THE CHILD PROCESS
    void stop(); // stop playing, kills the child process
    void setLoop(short); // set if looping
    void setTime(double); // play the whole thing for an amount of time
    void setInTime(double); // set a fade in and amount of time
    void setOutTime(double); // set a fade out and amount of time
    void setMaxOutputLevel(double); // set the maximum output lvl betwn 0 and 1
    short getIsLive();  // returns true or FALSE if a stop is needed
    short donep(); // returns if done playing the audio
};

#endif
