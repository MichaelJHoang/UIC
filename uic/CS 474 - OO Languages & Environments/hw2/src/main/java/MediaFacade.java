/*


    Source: https://refactoring.guru/design-patterns/facade/java/example


 */

import java.io.File;

@FacadeAnnotation(name = "VideoFile", clientAccessible = false)
class VideoFile
{
    private String name;
    private String codecType;

    public VideoFile(String name)
    {
        this.name = name;
        this.codecType = name.substring(name.indexOf(".") + 1);
    }

    public String getCodecType()
    {
        return codecType;
    }

    public String getName()
    {
        return name;
    }
}

@FacadeAnnotation(name = "Codec", clientAccessible = false)
interface Codec {}

@FacadeAnnotation(name = "MPEG4CompressionCodec", clientAccessible = false)
class MPEG4CompressionCodec implements Codec
{
    public String type = "mp4";
}

@FacadeAnnotation(name = "OggCompressionCodec", clientAccessible = false)
class OggCompressionCodec implements Codec
{
    public String type = "ogg";
}

@FacadeAnnotation(name = "CodecFactory", clientAccessible = false)
class CodecFactory
{
    public static Codec extract(VideoFile file)
    {
        String type = file.getCodecType();
        if (type.equals("mp4"))
        {
            System.out.println("CodecFactory: extracting mpeg audio...");
            return new MPEG4CompressionCodec();
        }
        else
        {
            System.out.println("CodecFactory: extracting ogg audio...");
            return new OggCompressionCodec();
        }
    }
}

@FacadeAnnotation(name = "BitrateReader", clientAccessible = false)
class BitrateReader
{
    public static VideoFile read(VideoFile file, Codec codec)
    {
        System.out.println("BitrateReader: reading file...");
        return file;
    }

    public static VideoFile convert(VideoFile buffer, Codec codec)
    {
        System.out.println("BitrateReader: writing file...");
        return buffer;
    }
}

@FacadeAnnotation(name = "AudioMixer", clientAccessible = false)
class AudioMixer
{
    public File fix(VideoFile result)
    {
        System.out.println("AudioMixer: fixing audio...");
        return new File("tmp");
    }
}

@FacadeAnnotation(name = "MediaFacade", clientAccessible = true)
public class MediaFacade
{
    @FacadeAnnotation(name = "MediaFacade.convertVideo", clientAccessible = true)
    public File convertVideo(String fileName, String format)
    {
        System.out.println("VideoConversionFacade: conversion started.");
        VideoFile file = new VideoFile(fileName);
        Codec sourceCodec = CodecFactory.extract(file);
        Codec destinationCodec;
        if (format.equals("mp4"))
        {
            destinationCodec = new OggCompressionCodec();
        } else
        {
            destinationCodec = new MPEG4CompressionCodec();
        }
        VideoFile buffer = BitrateReader.read(file, sourceCodec);
        VideoFile intermediateResult = BitrateReader.convert(buffer, destinationCodec);
        File result = (new AudioMixer()).fix(intermediateResult);
        System.out.println("VideoConversionFacade: conversion completed.");
        return result;
    }
}