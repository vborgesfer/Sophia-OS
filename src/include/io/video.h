/**
 * @file video.h
 * @brief Simple video driver for VGA
 * @author Victor Borges
 * @date Mar 12, 2011
 */

#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <types.h>

/* Normal and Dark/Light foreground */
#define VIDEO_FG_BLACK     0  /**< Black video foreground color */
#define VIDEO_FG_DKGRAY    8  /**< Dark gray video foreground color */
#define VIDEO_FG_BLUE      1  /**< Blue video foreground color */
#define VIDEO_FG_LTBLUE    9  /**< Light blue video foreground color */
#define VIDEO_FG_GREEN     2  /**< Green video foreground color */
#define VIDEO_FG_LTGREEN   10 /**< Light green video foreground color */
#define VIDEO_FG_CYAN      3  /**< Cyan video foreground color */
#define VIDEO_FG_LTCYAN    11 /**< Light cyan video foreground color */
#define VIDEO_FG_RED       4  /**< Red video foreground color */
#define VIDEO_FG_LTRED     12 /**< Light red video foreground color */
#define VIDEO_FG_MAGENTA   5  /**< Magenta video foreground color */
#define VIDEO_FG_LTMAGENTA 13 /**< Light magenta video foreground color */
#define VIDEO_FG_BROWN     6  /**< Brown video foreground color */
#define VIDEO_FG_YELLOW    14 /**< Yellow video foreground color */
#define VIDEO_FG_LTGRAY    7  /**< Light gray video foreground color */
#define VIDEO_FG_WHITE     15 /**< White video foreground color */

/* Background */
#define VIDEO_BG_DEFAULT	(0 << 4) /**< Black video background color */
#define VIDEO_BG_BLACK		(0 << 4) /**< Black video background color */
#define VIDEO_BG_BLUE		(1 << 4) /**< Blue video background color */
#define VIDEO_BG_GREEN		(2 << 4) /**< Green video background color */
#define VIDEO_BG_CYAN		(3 << 4) /**< Cyan video background color */
#define VIDEO_BG_RED		(4 << 4) /**< Red video background color */
#define VIDEO_BG_MAGENTA	(5 << 4) /**< Magenta video background color */
#define VIDEO_BG_BROWN		(6 << 4) /**< Brown video background color */
#define VIDEO_BG_LTGRAY		(7 << 4) /**< Light gray video background color */

/** Blinking foreground color */
#define VIDEO_FG_BLINKING  (1 << 7) 

/**
 * Initialize simple video driver
 */
void video_setup();

/**
 * Choose default color
 * @param color		Default color chose
 **/
void video_set_color(byte color);

/**
 * Print a character using default status
 * @param c		Character
 **/
inline void video_printc(const char c);

/**
 * Print a string using default status
 * @param str	String
 **/
void video_print(const char * str);

/**
 * Print a formatted string using default status
 * @param str	format
 * @note STD C format supported: \%s, \%d, \%b and \%x
 **/
void video_printf(char * format, ...);

/**
 * Updates default status adding a new line
 **/
void video_newline();

/**
 * Scrol the text in video
 * @param nblines	Number of lines to scrol
 **/
void video_scrolling(int nblines);

/**
 * Clean video
 * @param bkColor	Background color to clean
 **/
void video_clear(byte bkColor);

/**
 * Update video cursor for the currently position
 **/
void video_update_cursor();

/**
 * Print a character chossing position
 * @param c			Character
 * @param color		Color chose
 * @param row		Line position
 * @param col		Column position
 * @note	This function do not update currently video status
 **/
void video_putc(char c, const byte color,
		const int row, const int col);

/**
 * Print a character chossing position
 * @param c			Character
 * @param color		Color chose
 * @param row		Line position
 * @param col		Column position
 * @note	This function do not update currently video status
 **/
void video_put(const char * str, byte color,
		const int row, const int col);

#endif /* _VIDEO_H_ */
