/*
 * Copyright 2007-2009 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the GPL v3 License.
 */
#ifndef PROJECT_H
#define PROJECT_H

class BString;
class Timeline;

class Project
{
public:
			Project();
			~Project();

	const char*	Title() const;
	float		Frequency() const;
	uint32		SampleRate() const;
	bigtime_t	Duration() const;

	Timeline *	GetTimeline() const;

	const char*	FileName() const;

	bool		IsModified() const;

	void		New();
	status_t	Load(const char* filename);
	status_t	Save();
	status_t	SaveAs(const char* filename);

private:
	char*		fFileName;
	BString		fTitle;
	float		fFrequency;
	uint32		fSampleRate;
	bigtime_t	fDuration;
	Timeline*	fTimeline;
	bool		fModified;
};

#endif // PROJECT_H
