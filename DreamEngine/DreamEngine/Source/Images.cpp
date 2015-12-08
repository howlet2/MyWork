#include "Images.h"

extern "C" {
#include "libjpeg/include/jpeglib.h"
#include "libpng/include/png.h"
#include "libpng/include/pngconf.h"
#include "libpng/include/pngstruct.h"
}


namespace DreamEngine
{
#define FILE_HEAR_SIZE 8

CImages::CImages(void):
m_pData(MATH_NULL),
m_height(0),
m_width(0),
m_texFormat(TF_UNKOWN),
m_pixelPerBytes(0)
{
}


CImages::~CImages(void)
{
	SAFE_DELETE_ARRY(m_pData);
}

m_byte* CImages::loadFromFile(const CString& fileName)
{
	CFileDataStream file;
	if (file.open(fileName, CFileDataStream::READ_BINARY))
	{
		SAFE_DELETE_ARRY(m_pData);
		m_byte header[FILE_HEAR_SIZE] = {0};
		if (file.read(header, sizeof(header)))
		{
			file.moveToBegin();

			if (isTga(header))
				initWithTgaFile(file);
			else if(isPng(header))
				initWithPngFile(file);
			else if(isJpeg(header))
				initWithJpegFile(file);
		}
		
		file.close();
	}
	return m_pData;
}

bool CImages::isTga(m_byte* header)
{
	m_byte		tgaUnComposeHeader[FILE_HEAR_SIZE]	=	{0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x0};   
	m_byte		tgaComposeHeader[FILE_HEAR_SIZE]	=	{0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0}; 

	return (memcmp(header, tgaUnComposeHeader, sizeof(tgaUnComposeHeader))==0 ||
			memcmp(header, tgaComposeHeader, sizeof(tgaComposeHeader))==0);
}

bool  CImages::isPng(m_byte* header)
{
	m_byte pngHeader[FILE_HEAR_SIZE]		= {0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a};

	return memcmp(pngHeader, header, sizeof(pngHeader)) == 0;
}

bool CImages::isJpeg(m_byte* header)
{
	static const unsigned char jpegHeader[2] = {0xFF, 0xD8};

	return memcmp(header, jpegHeader, sizeof(jpegHeader)) == 0;
}

m_byte* CImages::initWithTgaFile(CFileDataStream& file)
{
	m_byte		tgaUnComposeHeader[12]	=	{0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	m_byte		tgaComposeHeader[12]	=	{0x0,0x0,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}; 
	m_byte		tgacompare[12]			=	{0};                           
	m_byte		header[6]				=	{0};  
	bool		isCompose				=   false;

	if (file.read(tgacompare, sizeof(tgacompare)))
	{
		if (memcmp(tgacompare, tgaUnComposeHeader, sizeof(tgacompare))==0)
		{
			isCompose = false;
		}
		else if(memcmp(tgaComposeHeader, tgaUnComposeHeader, sizeof(tgaComposeHeader))==0)
		{
			isCompose = true;
		}
		else
		{
			return MATH_NULL;
		}

		if (!file.read(header, sizeof(header)))
			return MATH_NULL;
	}

	m_width			= header[1]*256+header[0];				//第12位和第13位表示宽度
	m_height		= header[3]*256+header[2];				//第14位和第15位表示高度
    m_pixelPerBytes = header[4]/8;							//每个像素占的字节数
	m_byte exInfo   = header[5];
	
	if (m_pixelPerBytes==4)
		m_texFormat = TF_R8G8B8A8;
	else if(m_pixelPerBytes==3)
		m_texFormat = TF_R8G8B8;

	int  imageSize  = m_width*m_height*m_pixelPerBytes;
	m_pData = new m_byte[imageSize]; 
	if (!file.read(m_pData, imageSize))
	{
		SAFE_DELETE_ARRY(m_pData);
		return MATH_NULL;
	}
	else
	{
		if (!isCompose)
		{
			_initUnComposeTgaFile(m_pData, imageSize);
		}
		else
		{
			_initComposeTgaFile(file, m_pData, imageSize);
		}
		
		bool needFlip = !(exInfo&0x20);		//0=图像原点在左下角 1=图像原点在左上角(屏幕原点是左上角)
		if (needFlip)
		{
			_flipTagFile(m_pData);
		}
	}
	return m_pData;
}

#define RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
	(unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
	((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
	((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
	((unsigned)(unsigned char)(va) << 24))

struct PngImgSource
{
	const m_byte *	pData;
	long			size;
	int				offset;
};

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	PngImgSource* isource = (PngImgSource*)png_get_io_ptr(png_ptr);

	if((int)(isource->offset + length) <= isource->size)
	{
		memcpy(data, isource->pData+isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

m_byte* CImages::initWithPngFile(CFileDataStream& fileData)
{
	m_texFormat = TF_UNKOWN;
	m_pixelPerBytes = 1;

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);  
	if (png_ptr != nullptr)
	{
		SAFE_DELETE_ARRY(m_pData);

		long	fileSize = static_cast<long>(fileData.getSize());
		m_byte* buff	 = new m_byte[fileSize];
		fileData.read(buff, fileSize);

		setjmp(png_jmpbuf(png_ptr));

		png_infop info_ptr = png_create_info_struct(png_ptr);
		PngImgSource imageSource;
		imageSource.pData    = buff;
		imageSource.size     = fileSize;
		imageSource.offset	 = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		png_read_info(png_ptr, info_ptr);
		m_width					= png_get_image_width(png_ptr, info_ptr);
		m_height				= png_get_image_height(png_ptr, info_ptr);
		png_byte bit_depth		= png_get_bit_depth(png_ptr, info_ptr);
		png_uint_32 color_type	= png_get_color_type(png_ptr, info_ptr);

		if (color_type==PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		else if (color_type==PNG_COLOR_TYPE_GRAY && bit_depth<8)
		{
			bit_depth = 8;
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}
		else if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}  
		else if (bit_depth==16)
		{
			png_set_strip_16(png_ptr);            
		} 
		else if (bit_depth<8)
		{
			png_set_packing(png_ptr);
		}
		png_read_update_info(png_ptr, info_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);
	
		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			{
				m_texFormat		= TF_L8;
				m_pixelPerBytes = 1;
			}break;
		//case PNG_COLOR_TYPE_GRAY_ALPHA:
			//_renderFormat = Texture2D::PixelFormat::AI88;
			//break;
		case PNG_COLOR_TYPE_RGB:
			{
				m_texFormat = TF_R8G8B8;
				m_pixelPerBytes = 3;
			}break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			{
				m_texFormat = TF_R8G8B8A8;
				m_pixelPerBytes = 4;
			}break;
		default:
			m_texFormat = TF_UNKOWN;
			break;
		}

		png_size_t rowbytes;
		png_bytep* row_pointers = new png_bytep[sizeof(png_bytep)*m_height];
		rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		int datalength = rowbytes*m_height;
		m_pData = new m_byte[datalength*sizeof(m_byte)];
		if (m_pData!=MATH_NULL || row_pointers!=MATH_NULL)
		{
			for (m_uint16 i=0; i<m_height; ++i)
				row_pointers[i] = m_pData+i*rowbytes;
		
			png_read_image(png_ptr, row_pointers);
			png_read_end(png_ptr, MATH_NULL);

			if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
			{
				m_uint32* fourBytes = (m_uint32*)m_pData;
				for(int i=0; i<m_width*m_height; i++)
				{
					m_byte* p = m_pData+i*4;
					fourBytes[i] = RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
				}
			}

			if (row_pointers != MATH_NULL)
				free(row_pointers);
		}

		if (png_ptr != nullptr)
			png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);

		SAFE_DELETE_ARRY(buff);
	}

	return m_pData;
}

struct my_error_mgr 
{
  struct jpeg_error_mgr pub;	
  jmp_buf setjmp_buffer;	
};
typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
//	(*cinfo->err->output_message) (cinfo);
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message) (cinfo, buffer);
	longjmp(myerr->setjmp_buffer, 1);
}

m_byte* CImages::initWithJpegFile(CFileDataStream& fileData)
{
	m_texFormat = TF_R8G8B8;
	m_pixelPerBytes = 3;

    struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

    JSAMPROW row_pointer[1] = {0};
    unsigned long location = 0;
    unsigned int i = 0;

    bool bRet = false;
    do 
    {
		cinfo.err = jpeg_std_error(&jerr.pub);
		jerr.pub.error_exit = my_error_exit;
	
		if (setjmp(jerr.setjmp_buffer)) 
		{
			jpeg_destroy_decompress(&cinfo);
			break;
		}
        jpeg_create_decompress( &cinfo );

		int   imgDataLen	 = fileData.getSize();
		m_byte* pBuffer		= new m_byte[imgDataLen];
		fileData.read(pBuffer, imgDataLen);
        jpeg_mem_src( &cinfo, pBuffer, imgDataLen );
        jpeg_read_header( &cinfo, true );

        if (cinfo.jpeg_color_space != JCS_RGB)
        {
            if (cinfo.jpeg_color_space==JCS_GRAYSCALE || cinfo.jpeg_color_space==JCS_YCbCr)
            {
                cinfo.out_color_space=JCS_RGB;
            }
        }
        else
        {
            break;
        }

        jpeg_start_decompress( &cinfo );

        m_width  = (short)(cinfo.output_width);
        m_height = (short)(cinfo.output_height);
        row_pointer[0] = new m_byte[cinfo.output_width*cinfo.output_components];

		int dataSize = cinfo.output_width*cinfo.output_height*cinfo.output_components;
        m_pData = new m_byte[dataSize];
		memset(m_pData, 0, dataSize);

        while( cinfo.output_scanline<cinfo.output_height )
        {
            jpeg_read_scanlines(&cinfo, row_pointer, 1);
            for( i=0; i<cinfo.output_width*cinfo.output_components;i++) 
            {
                m_pData[location++] = row_pointer[0][i];
            }
        }
        jpeg_destroy_decompress( &cinfo );
          
        bRet = true;
		SAFE_DELETE_ARRY(row_pointer[0]);
    } while (0);

    return m_pData;
}

void CImages::_initComposeTgaFile(CFileDataStream& fileData, m_byte* pData, int dataSize)
{
	int pixelCount = m_height*m_width;  
	int curPixel = 0;  
	m_uint8 ucColorBuffer[4] = {0};  
	do{  
		m_byte chunkheader = 0;  
		fileData.read((char*)&chunkheader, sizeof(m_byte));  
		if(chunkheader & 0x80)						//B类数据  
		{  
			int iCnt = (chunkheader & 0x7f) + 1;	//计算连续的颜色值重复的像素数。注意：最高位的1是标记位，所以要特殊处理  
			fileData.read((char*)ucColorBuffer, m_pixelPerBytes);  
			for(int i = 0; i < iCnt; i++)  
			{  
				pData[curPixel*m_pixelPerBytes + 0] = ucColorBuffer[0];  
				pData[curPixel*m_pixelPerBytes + 1] = ucColorBuffer[1];  
				pData[curPixel*m_pixelPerBytes + 2] = ucColorBuffer[2];  
				if(m_pixelPerBytes == 4)  
				{  
					pData[curPixel*m_pixelPerBytes + 3] = ucColorBuffer[3];  
				}  
				curPixel++;  
				if(curPixel > pixelCount)  
					return ;  
			}  
		}
		else											//A类数据  
		{  
			int iCnt = chunkheader + 1;					//颜色值不重复的像素数量，注意要加一  
			for(int i = 0; i < iCnt; i++)  
			{                                               
				fileData.read((char*)ucColorBuffer, m_pixelPerBytes);  
				m_pData[curPixel*m_pixelPerBytes + 0] = ucColorBuffer[0];  
				m_pData[curPixel*m_pixelPerBytes + 1] = ucColorBuffer[1];  
				m_pData[curPixel*m_pixelPerBytes + 2] = ucColorBuffer[2];  
				if(m_pixelPerBytes == 32)  
				{  
					m_pData[curPixel*m_pixelPerBytes+3] = ucColorBuffer[3];  
				}  

				curPixel++;  
				if(curPixel > pixelCount)  
				{
					return;  
				}  
			}  
		}
	}while(curPixel < pixelCount);
}

void CImages::_initUnComposeTgaFile(m_byte* pData, int dataSize)
{
	for(int i=0; i<int(dataSize); i+=m_pixelPerBytes)     
	{   
		//把BGR转成RGB     
		pData[i] ^= pData[i+2] ^= pData[i] ^= pData[i+2];	//等效std::swap(pData[i], pData[i+2]);
	}  
}

void CImages::_flipTagFile(m_byte* pData)
{
	int rowbytes = m_width*m_pixelPerBytes;
	m_byte *pRow =  new m_byte[rowbytes];

	if (pRow == MATH_NULL) return;

	for(int y = 0; y < (m_height/2); y++ )
	{
		memcpy(pRow,	&pData[y*rowbytes],	rowbytes);
		memcpy(&pData[y*rowbytes], &pData[(m_height-(y+1))*rowbytes], rowbytes);
		memcpy(&pData[(m_height-(y+1))*rowbytes], pRow, rowbytes);
	}
	SAFE_DELETE(pRow);
}

}

