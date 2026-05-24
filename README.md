# dlg-filelister
Linux utility to list contents of a DLG-BBs (Amiga) file area

# What do I need this program for?

DLG-filelister prints the list of files contained in a file area (a directory) of the famous BBS program for Amiga, DLG-BBs.

This BBS creates files in proprietary format to manage its file areas. Wanting to export said file area to another BBS, which however runs under Linux, I found it useful to create a filelister that provides the list in text format.

Below is an example of output.

```
227 fenstr32.lha                           185134 05-06-1992 14:00 Sysop                   0 Operates on requesters,window,screen etc                    
213 FFAST102.LHA                            15896 08-04-1992 14:00 Sysop                   1 Find Fast - good fast file&dir searcher.                    
585 FFILE114.LHA                            19895 07-12-1993 13:00 Sysop                   1 Find File v1.4 - file location and searc                    
287 FF_101.LHA                              27211 28-10-1992 13:00 SYSOP                   1 A file find utility for use under Workbench 2.04 or later   
654 FHSPRD17.LHA                            74178 02-01-1994 16:49 Sysop                   0 FHSpread v1.71 - Spreadsheet written in GFABASIC            
754 FICON16.ADS                              2759 29-08-1994 06:19 SkyTick v3.22           0 ForceIcon v1.6 - long description                           
755 FICON16.LHA                             96788 29-08-1994 06:19 SkyTick v3.22           1 ForceIcon v1.6 - set/change position and/or look of CD-ROM  
701 fileid14.lha                            38824 16-03-1994 20:18 Sysop                   9 Fileid v1.4 - Gives res./colors/etc for pics (IFF,GIF,JPEG  
594 FILELO10.LHA                            38670 07-12-1993 13:00 Sysop                   0 FileLogger v1.0 - Logger for disks                          
```

# Remarks
The Amiga filesystem was case insensitive. The file "File.DAT", under Amiga, is the same as "file.dat".

Under Linux, however, they are two different files. I therefore had to implement routines that "find" the right file and open it correctly.

Another problem was the recognition of numerical data stored in Amiga files. They are in fact represented in "BigEndian" mode, while Linux works in "LittleEndian" mode. I solved the problem using functions (ntohl(), ntohs()) specific to socket programming.
