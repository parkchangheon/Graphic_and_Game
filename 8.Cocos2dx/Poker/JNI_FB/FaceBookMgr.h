struct FacebookUserData
{
public:
	std::string fb_id;
	std::string fb_name;
	std::string fb_email;
	std::string fb_photoUrl;
};
#define FACEBOOK_OBJECT "org/cocos2dx/cpp/FacebookMgr"


#pragma once
class FaceBookMgr : public Singleton <FaceBookMgr>
{
public:
	class Listener
	{
	public:
		// 팝업이 로딩되었을 때
		virtual void onFacebookEvent(const int resultCode, const std::string paramStr) = 0;
	};

	FacebookUserData m_UserData;
public:
	FaceBookMgr();
	void LoginSession();
	void SetFacebookUserData();
};



template <typename T> class Singleton
{
private:
	/** \brief Explicit private copy constructor. This is a forbidden operation.*/
	Singleton(const Singleton<T>&);

	/** \brief Private operator= . This is a forbidden operation. */
	Singleton& operator=(const Singleton<T>&);

protected:
	static T* msSingleton;

public:
	Singleton(void)
	{
		NXASSERT(!msSingleton); msSingleton = static_cast<T*>(this);
	}
	~Singleton(void)
	{
		NXASSERT(msSingleton); msSingleton = 0;
	}
	static T& getSingleton(void)
	{
		NXASSERT(msSingleton); return (*msSingleton);
	}
	static T* getSingletonPtr(void)
	{
		return msSingleton;
	}
};