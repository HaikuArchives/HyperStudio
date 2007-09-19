
#ifndef PROJECT_H
#define PROJECT_H

class BString;
class TimeLine;

class Project
{
public:
	Project();
	~Project();

	const char* Title() const { return fTitle.String(); }
	float Frequency() const { return fFrequency; }
	uint32 SampleRate() const { return fSampleRate; }
	bigtime_t Duration() const { return fDuration; }

	TimeLine *GetTimeLine() const;

	const char* Directory() const { return fDirectory; }
	const char* FileName() const { return fFileName; }

	bool IsModified() const { return fModified; }

	void Load(const char* filename);
	void Save();
	void SaveAs(const char* path, const char* filename);

private:
	char* fDirectory;
	char* fFileName;
	BString fTitle;
	float fFrequency;
	uint32 fSampleRate;
	bigtime_t fDuration;
	TimeLine *fTimeLine;
	bool fModified;
};

extern Project *project;

#endif // PROJECT_H
