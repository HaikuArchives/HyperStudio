/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#include <Directory.h>
#include <Entry.h>
#include <File.h>
#include <Message.h>
#include <String.h>

#include "HyperionDebug.h"
#include "Project.h"
#include "TimeLine.h"

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

status_t
Project::Load(const char* filename)
{
	status_t err;
	entry_ref ref;
	BFile file;

	// Get entry ref for path
	err = get_ref_for_path(filename, &ref);
	if (err != B_OK)
		return err;

	// Load file from reference
	err = file.SetTo(&ref, B_READ_ONLY);
	if (err != B_OK)
		return err;
	if (fFileName)
		(void)free(fFileName);
	fFileName = strdup(filename);

	// Unflatten file to a message
	BMessage msg;
	err = msg.Unflatten(&file);
	if (err != B_OK)
		return err;
	msg.FindString("title", 0, &fTitle);
	msg.FindFloat("frequency", 0, &fFrequency);
	msg.FindInt32("samplerate", (int32*)&fSampleRate);
	msg.FindInt64("duration", 0, &fDuration);
	fModified = false;

	return B_OK;
}

status_t
Project::Save()
{
	BDirectory dir;
	BEntry entry(fFileName);
	BFile newFile;
	status_t err;

	// Get parent directory
	entry.GetParent(&dir);

	// Create file entry
	err = entry.InitCheck();
	if (err != B_OK)
		return err;
	dir.CreateFile(fFileName, &newFile);

	// Save the project file
	BMessage msg('HPRJ');
	msg.AddString("title", fTitle);
	msg.AddFloat("frequency", fFrequency);
	msg.AddInt32("samplerate", (int32)fSampleRate);
	msg.AddInt64("duration", fDuration);
	msg.Flatten(&newFile);
	fModified = false;

	return B_OK;
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
