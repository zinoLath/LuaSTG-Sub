#include "slow/ByteArray.hpp"
#include "pch.hpp"

namespace slow
{
    inline b8 is_pow2(size_t v)
    {
        return (v & (v - 1)) == 0;
    }
    
    class ByteArray : public Object<IByteArray>
    {
    private:
        u8* _data;
        u8* _ptr;
        u32 _realsize;
        u32 _size;
        u32 _align;
        bool _resizable;
    private:
        void _clear()
        {
            if (_data != nullptr)
            {
                ::HeapFree(::GetProcessHeap(), 0, _data);
            }
            _data = nullptr;
            _ptr = nullptr;
            _realsize = 0;
            _size = 0;
            _align = 0;
        }
        void _alloc(size_t size_, size_t align_)
        {
            if ((align_ != 0) && !is_pow2(align_))
                return; // 不支持的对齐，必须为二次幂，或者0代表默认对齐
            if (align_ > MEMORY_ALLOCATION_ALIGNMENT)
            {
                _realsize = size_ + align_; // 至少分配这么多的空间用于对齐
                _data = (u8*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, _realsize);
                size_t left = (size_t)_data % align_;
                if (left != 0)
                {
                    // 手动对齐
                    _ptr = _data + (align_ - left);
                }
                else
                {
                    _ptr = _data;
                }
            }
            else
            {
                // 已经符合对齐要求
                _realsize = size_;
                _data = (u8*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, _realsize);
                _ptr = _data;
            }
        }
    public:
        u8view view() const
        {
            return u8view(data(), size());
        }
        u8* data() const
        {
            return _ptr;
        }
        u32 size() const
        {
            return _size;
        }
        b8 resizable() const
        {
            return _resizable;
        }
        u32 align() const
        {
            return _align;
        }
        b8 resize(u32 size_, u32 align_)
        {
            if (!_resizable)
                return false;
            _clear();
            _size = size_;
            _align = align_;
            _alloc(size_, align_);
            return _ptr != nullptr;
        }
        
        #define _offset_check_light() if (offset >= _size) return false;
        #define _offset_check(T) if (((u32)sizeof(T) - 1 + offset) >= _size) return false;
        #define _write(T) *(T*)(_ptr + offset) = v;
        #define _write_align_check(T) if ((offset % sizeof(T)) != 0) return false; _write(T);
        #define _read(T) *v = *(T*)(_ptr + offset);
        #define _read_align_check(T) if ((offset % sizeof(T)) != 0) return false; _read(T);
        
        b8 writeu8(u8 v, u32 offset)
        {
            _offset_check_light();
            _write(u8);
            return true;
        }
        b8 writeu16(u16 v, u32 offset)
        {
            _offset_check(u16);
            _write_align_check(u16);
            return true;
        }
        b8 writeu32(u32 v, u32 offset)
        {
            _offset_check(u32);
            _write_align_check(u32);
            return true;
        }
        b8 writeu64(u64 v, u32 offset)
        {
            _offset_check(u64);
            _write_align_check(u64);
            return true;
        }
        
        b8 writei8(i8 v, u32 offset)
        {
            _offset_check_light();
            _write(i8);
            return true;
        }
        b8 writei16(i16 v, u32 offset)
        {
            _offset_check(i16);
            _write_align_check(i16);
            return true;
        }
        b8 writei32(i32 v, u32 offset)
        {
            _offset_check(i32);
            _write_align_check(i32);
            return true;
        }
        b8 writei64(i64 v, u32 offset)
        {
            _offset_check(i64);
            _write_align_check(i64);
            return true;
        }
        
        b8 writef32(f32 v, u32 offset)
        {
            _offset_check(f32);
            _write_align_check(f32);
            return true;
        }
        b8 writef64(f64 v, u32 offset)
        {
            _offset_check(f64);
            _write_align_check(f64);
            return true;
        }
        
        b8 readu8(u8* v, u32 offset) const
        {
            _offset_check_light();
            _read(u8);
            return true;
        }
        b8 readu16(u16* v, u32 offset) const
        {
            _offset_check(u16);
            _read_align_check(u16);
            return true;
        }
        b8 readu32(u32* v, u32 offset) const
        {
            _offset_check(u32);
            _read_align_check(u32);
            return true;
        }
        b8 readu64(u64* v, u32 offset) const
        {
            _offset_check(u64);
            _read_align_check(u64);
            return true;
        }
        
        b8 readi8(i8* v, u32 offset) const
        {
            _offset_check_light();
            _read(i8);
            return true;
        }
        b8 readi16(i16* v, u32 offset) const
        {
            _offset_check(i16);
            _read_align_check(i16);
            return true;
        }
        b8 readi32(i32* v, u32 offset) const
        {
            _offset_check(i32);
            _read_align_check(i32);
            return true;
        }
        b8 readi64(i64* v, u32 offset) const
        {
            _offset_check(i64);
            _read_align_check(i64);
            return true;
        }
        
        b8 readf32(f32* v, u32 offset) const
        {
            _offset_check(f32);
            _read_align_check(f32);
            return true;
        }
        b8 readf64(f64* v, u32 offset) const
        {
            _offset_check(f64);
            _read_align_check(f64);
            return true;
        }
        
        #undef _offset_check_light
        #undef _offset_check
        #undef _write
        #undef _write_align_check
        #undef _read
        #undef _read_align_check
    public:
        ByteArray()
            : _data(nullptr)
            , _ptr(nullptr)
            , _realsize(0)
            , _size(0)
            , _align(0)
            , _resizable(true)
        {
        }
        ByteArray(u32 size_, u32 align_, b8 resizable_)
            : _data(nullptr)
            , _ptr(nullptr)
            , _realsize(0)
            , _size(size_)
            , _align(align_)
            , _resizable(resizable_)
        {
            _alloc(size_, align_);
            if (_ptr == nullptr)
                throw;
        }
        virtual ~ByteArray()
        {
            _clear();
        }
    };
    
    b8 createByteArray(IByteArray** obj, u32 size, u32 align, b8 resizable)
    {
        try
        {
            ByteArray* ins = new ByteArray(size, align, resizable);
            *obj = dynamic_cast<IByteArray*>(ins);
            return true;
        }
        catch (...)
        {
            *obj = nullptr;
            return false;
        }
    }
    b8 createByteArrayFromFile(IByteArray** obj, c8view path, u32 align)
    {
        try
        {
            Microsoft::WRL::Wrappers::FileHandle file;
            file.Attach(::CreateFileW(_to_wide(path.data).c_str(), 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));
            if (!file.IsValid())
                return false;
            LARGE_INTEGER file_pos = {}; file_pos.QuadPart = 0;
            if (!::SetFilePointerEx(file.Get(), file_pos, NULL, FILE_BEGIN))
                return false;
            LARGE_INTEGER file_size = {};
            if (!::GetFileSizeEx(file.Get(), &file_size))
                return false;
            if (file_size.HighPart != 0)
                return false;
            object_ptr<ByteArray> buf;
            buf.setDirect(new ByteArray(file_size.LowPart, align, false));
            DWORD readbs = 0;
            if (!::ReadFile(file.Get(), buf->data(), file_size.LowPart, &readbs, NULL))
                return false;
            if (file_size.LowPart != readbs)
                return false;
            file.Close();
            *obj = dynamic_cast<IByteArray*>(buf.getOwnership());
            return true;
        }
        catch (...)
        {
            *obj = nullptr;
            return false;
        }
    }
}
