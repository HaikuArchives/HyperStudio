/*
 * Copyright 2007 Pier Luigi Fiorini. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		Pier Luigi Fiorini, pierluigi.fiorini@gmail.com
 */

#ifndef PROJECT_H
#define PROJECT_H

class BString;
class TimeLine;

class Project {
	public:
		Project();
		~Project();

		const char* Title() const { return fTitle.String(); }
		float Frequency() const { return fFrequency; }
		uint32 SampleRate() const { return fSampleRate; }
		bigtime_t Duration() const { return fDuration; }

		TimeLine *GetTimeLine() const;

		const char* FileName() const { return fFileName; }

		bool IsModified() const { return fModified; }

		void New();
		status_t Load(const char* filename);
		status_t Save();
		void SaveAs(const char* filename);

	private:
		char* fFileName;
		BString fTitle;
		float fFrequency;
		uint32 fSampleRate;
		bigtime_t fDuration;
		TimeLine *fTimeLine;
		bool fModified;
};

#endif // PROJECT_H
