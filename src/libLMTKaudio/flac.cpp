#include "flac.h"

namespace audio {

    FLAC::FLAC(unsigned long length) : AudioTrack(length)
    {
        // flac specific info
    }

    FLAC::FLAC(unsigned long length, unsigned long sample_rate)
        : AudioTrack(length, sample_rate)
    {
    }

    FLAC::FLAC(std::string path) : AudioTrack()
    {
        readFile(path);
    }

    bool FLAC::readFile(std::string path)
    {
        FILE* fp = fopen(path.c_str(), "rb");
        if (fp == NULL) throw std::runtime_error("file not found");

        FLACDecoder decoder;
        if (!decoder) throw 0xF;

        decoder.set_md5_checking(true);
        FLAC__StreamDecoderInitStatus init_stat = decoder.init(fp);
        if (init_stat != FLAC__STREAM_DECODER_INIT_STATUS_OK) 
            throw std::runtime_error("file read error");

        if (!decoder.process_until_end_of_stream()) 
            throw std::runtime_error("file read error");

        fclose(fp);

        *this = decoder.get();

        return false;
    }

    bool FLAC::writeFile(std::string path)
    {
        return false; // TODO
    }


    FLAC FLAC::FLACDecoder::get()
    {
        if (!finished) throw 0xF; //
        return *out;
    }

    FLAC__StreamDecoderWriteStatus FLAC::FLACDecoder::write_callback(const FLAC__Frame* frame, const FLAC__int32* const* buffer)
    {
        // ASSUMES out is alr. constructed
        // TODO add variable stuff support
        if (out->sampleLength() == 0) throw std::runtime_error("sample length must be > 0");
        if (out->channels() != 2) throw std::invalid_argument("unsupported");

        //const FLAC__uint32 total_size = (FLAC__uint32)(out->sampleLength() * out->channels() * (bit_depth / 8));

        for (unsigned long i = 0; i < frame->header.blocksize; i++)
        {
            audio_sample s{};
            s.left = (float)buffer[0][i] / utils::uint_max_val(bit_depth); // bitdepth max int
            s.right = (float)buffer[1][i] / utils::uint_max_val(bit_depth);
            out->audio[out->currentPos()] = s;
            (void)out->nextSample();
        }

        finished = true;
        return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
    }

    void FLAC::FLACDecoder::metadata_callback(const FLAC__StreamMetadata* metadata)
    {
        if (metadata->type != FLAC__METADATA_TYPE_STREAMINFO) return;

        unsigned long sample_len =
            (unsigned long)metadata->data.stream_info.total_samples;
        unsigned long sample_rate =
            (unsigned long)metadata->data.stream_info.sample_rate;
        unsigned int channels = metadata->data.stream_info.channels;

        // TODO handle num channels
        if (channels != 2) throw std::invalid_argument("unsupported");
        out = new FLAC(sample_len, sample_rate);

        bit_depth = metadata->data.stream_info.bits_per_sample;
    }

    void FLAC::FLACDecoder::error_callback(FLAC__StreamDecoderErrorStatus status)
    {
        throw std::runtime_error("FLAC decoder error: " + std::to_string(status));
        return; // TODO handle
    }

}
