#pragma once

template <typename T>
class Singleton
{
protected:
    // Constructor and destructor
    Singleton () { };
    ~Singleton () { };

public:
    // public interface
    static T *GetInstance ( bool memoryTraced = true )
    {
        m_Singleton = GetExistingInstance();

        if (m_Singleton == NULL)
        {
            if (memoryTraced)
            {
                m_Singleton = LUDO_NEW T;
            }
            else
            {
                m_Singleton = new T;
            }
        }

        return (static_cast<T*> (m_Singleton));
    }

    static T *GetExistingInstance ()
    {
        if (m_Singleton == NULL)
        {
            return NULL;
        }

        return (static_cast<T*> (m_Singleton));
    }

    static void Destroy()
    {
        LUDO_SAFE_DELETE(m_Singleton)
    }

private:
    // Unique instance
    static T *m_Singleton;
};

template <typename T> T *Singleton<T>::m_Singleton = NULL;
