#include <kolibriLib/sound.hpp>
#include <stdlib.h>

using namespace KolibriLib;
using namespace Sound;

KolibriLib::Sound::SpeakerSound::SpeakerSound(std::size_t size)
{
	data = (Data *) malloc(size * );
}

uint8_t KolibriLib::Sound::SpeakerSound::Data::GetNote() const
{
	return note;
}

bool PlayOnSpeaker(SpeakerSound *data)
{
       
}