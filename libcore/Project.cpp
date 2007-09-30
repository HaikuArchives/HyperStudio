
#include <Directory.h>
#include <Entry.h>
#include <File.h>
#include <Message.h>
#include <String.h>

#include "HyperionDebug.h"
#include "Exception.h"
#include "Project.h"
#include "TimeLine.h"

using namespace Hyperion;

static uint32 new_project_count = 0;

Project::Project()
{
	// Initialize the project
	New();

	// Initialize members
	fTimeLine = new TimeLine();
}

Project::~Project()
{
	delete fTimeLine;
	if (fFileName)
		(void)free(fFileName);
}

TimeLine *
Project::GetTimeLine() const
{
	return fTimeLine;
}

void
Project::New()
{
	fFileName = NULL;
	fFrequency = 44100.0f;
	fSampleRate = 24;
	fDuration = 1000000000;
	fModified = false;
	fTitle = "";
	fTitle << "Untitled " << ++new_project_count;
}

void
Project::Load(const char* filename)
{
	status_t err;
	entry_ref ref;
	BFile file;

	// Get entry ref for path
	err = get_ref_for_path(filename, &ref);
	switch (err)
	{
	case B_OK:
		break;
	case B_ENTRY_NOT_FOUND: {
			BString exMsg;
			exMsg << "Project file \"" << filename << "\" not found.";
			throw Exception(exMsg.String());
		}
	case B_NO_MEMORY:
		throw Exception("Out of memory!");
	default:
		throw Exception("Unknown error!");
	}

	// Load file from reference
	err = file.SetTo(&ref, B_READ_ONLY);
	switch (err)
	{
	case B_OK:
		break;
	case B_PERMISSION_DENIED: {
			BString exMsg;
			exMsg << "Permission denied opening project file";
			exMsg << " \"" << filename << "\".";
			throw Exception(exMsg.String());
		}
	case B_NO_MEMORY:
		throw Exception("Out of memory!");
	default:
		throw Exception("Unknown error!");
	}
	if (fFileName)
		(void)free(fFileName);
	fFileName = strdup(filename);

	// Unflatten file to a message
	BMessage msg;
	if (msg.Unflatten(&file) != B_OK)
	{
		BString exMsg;
		exMsg << "Failed to read project file";
		exMsg << " \"" << filename << "\".";
		throw Exception(exMsg.String());
	}
	msg.FindString("title", 0, &fTitle);
	msg.FindFloat("frequency", 0, &fFrequency);
	msg.FindInt32("samplerate", (int32*)&fSampleRate);
	msg.FindInt64("duration", 0, &fDuration);
	fModified = false;
}

void
Project::Save()
{
	BDirectory dir;
	BEntry entry(fFileName);
	entry.GetParent(&dir);
	BFile newFile;

	// Create file entry
	if (entry.InitCheck() != B_OK)
		throw Exception("Can't overwrite file.");
	dir.CreateFile(fFileName, &newFile);

	// Save the project file
	BMessage msg('HPRJ');
	msg.AddString("title", fTitle);
	msg.AddFloat("frequency", fFrequency);
	msg.AddInt32("samplerate", (int32)fSampleRate);
	msg.AddInt64("duration", fDuration);
	msg.Flatten(&newFile);
	fModified = false;
}

void
Project::SaveAs(const char* filename)
{
	// Set new file name
	if (fFileName)
		(void)free(fFileName);
	fFileName = strdup(filename);

	// Save
	Save();
}
