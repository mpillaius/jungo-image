// FileStreams.h

#ifndef __FILESTREAMS_H
#define __FILESTREAMS_H

#ifdef WIN32
#include "../../Windows/FileIO.h"
#else
#include "../../Common/C_FileIO.h"
#endif

#include "../IStream.h"
#include "../../Common/MyCom.h"

class CInFileStream: 
  public IInStream,
  public IStreamGetSize,
  public CMyUnknownImp
{
public:
  #ifdef WIN32
  NWindows::NFile::NIO::CInFile File;
  #else
  NC::NFile::NIO::CInFile File;
  #endif
  CInFileStream() {}
  virtual ~CInFileStream() {}

  bool Open(LPCTSTR fileName);
  #ifdef WIN32
  #ifndef _UNICODE
  bool Open(LPCWSTR fileName);
  #endif
  #endif

  MY_UNKNOWN_IMP2(IInStream, IStreamGetSize)

  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(ReadPart)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);

  STDMETHOD(GetSize)(UInt64 *size);
};

#ifndef _WIN32_WCE
class CStdInFileStream: 
  public ISequentialInStream,
  public CMyUnknownImp
{
public:
  // HANDLE File;
  // CStdInFileStream() File(INVALID_HANDLE_VALUE): {}
  // void Open() { File = GetStdHandle(STD_INPUT_HANDLE); };
  MY_UNKNOWN_IMP

  virtual ~CStdInFileStream() {}
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(ReadPart)(void *data, UInt32 size, UInt32 *processedSize);
};
#endif

class COutFileStream: 
  public IOutStream,
  public CMyUnknownImp
{
public:
  #ifdef WIN32
  NWindows::NFile::NIO::COutFile File;
  #else
  NC::NFile::NIO::COutFile File;
  #endif
  virtual ~COutFileStream() {}
  bool Create(LPCTSTR fileName, bool createAlways);
  #ifdef WIN32
  #ifndef _UNICODE
  bool Create(LPCWSTR fileName, bool createAlways);
  #endif
  #endif
  
  MY_UNKNOWN_IMP1(IOutStream)

  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(WritePart)(const void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
  STDMETHOD(SetSize)(Int64 newSize);
};

#ifndef _WIN32_WCE
class CStdOutFileStream: 
  public ISequentialOutStream,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP

  virtual ~CStdOutFileStream() {}
  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(WritePart)(const void *data, UInt32 size, UInt32 *processedSize);
};
#endif

class CMemInFileStream: 
  public ISequentialInStream,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP
  UInt32 _pos, _buf_size;
  void *_buf;

  CMemInFileStream() { _pos = 0; _buf = NULL; }
  virtual ~CMemInFileStream() {}
  void SetBuffer(void *buf, int buf_size) { _buf = buf; _buf_size = buf_size; }
  STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(ReadPart)(void *data, UInt32 size, UInt32 *processedSize);
};

class CMemOutFileStream: 
  public ISequentialOutStream,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP
  UInt32 _pos, _buf_size;
  void *_buf;

  CMemOutFileStream() { _pos = 0; _buf = NULL; }
  UInt32 DataSize(void) { return _pos; }
  virtual ~CMemOutFileStream() {}
  void SetBuffer(void *buf, int buf_size) { _buf = buf; _buf_size = buf_size; }
  STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
  STDMETHOD(WritePart)(const void *data, UInt32 size, UInt32 *processedSize);
};

#endif
