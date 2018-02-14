/**

  Copyright (c) 2011, C2Serve (http://www.c2serve.eu)
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement: "This product includes software of the C2Serve project".
  4. Neither the name of the C2Serve project nor the
     names of its contributors may be used to endorse or promote products
     derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY C2SERVE ''AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL C2SERVE BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef C2STASKQUEUE_H_
#define C2STASKQUEUE_H_

#include "C2SThreadQueue.h"
#include "C2SThreadTaskInterface.h"

namespace c2s
{
  namespace thread
  {

    class C2STaskQueue;

    class C2STaskQueueRunnable
    {
    public:

      C2STaskQueueRunnable( C2STaskQueue *pQueue )
        : m_pQueue( pQueue )
      {};

      inline void run();

    private:

      C2STaskQueue *m_pQueue;

    };

    class C2STaskQueue : public C2SThreadBase
    {
    public:

      C2STaskQueue( unsigned int iNumThreads )
        : m_bIsRunning( false ),
          m_bStartingNextTask( false )
      {
        for ( unsigned int i = 0; i < iNumThreads; ++i )
        {
          m_runnables.push_back( C2STaskQueueRunnable( this ) );
          m_workers.queue( &( m_runnables.back() ) );
        }
      }

      virtual ~C2STaskQueue()
      {
        this->join();
      }

      void join()
      {
        C2SLock<C2SMutex> lock( &m_runningMutex );
        while( m_tasks.size() > 0 )
          ;
        m_workers.join();
      }

      void queue( C2SThreadTaskInterface *task )
      {
        C2SLock<C2SMutex> lock( &m_mutex );
        m_tasks.push_back( task );
        if ( !m_bIsRunning )
        {
          m_runningMutex.lock();
          m_bIsRunning = true;
          this->start();
        }
      }

      void run()
      {
        volatile bool bContinue = true;

        while( bContinue )
        {
          m_detachMutex.lock();
          //TODO
#ifdef WINXX
          while( m_bStartingNextTask )
            ;
#endif
          if ( !m_tasks.size() )
          {
            m_detachMutex.unlock();
            break;
          }

          m_bStartingNextTask = true;
          m_workers.start();
        }

        m_bIsRunning = false;
        m_runningMutex.unlock();
      }

    protected:

      friend class C2STaskQueueRunnable;

      C2SThreadTaskInterface *detach()
      {
        C2SLock<C2SMutex> lock( &m_mutex );

        assert( m_tasks.size() );

        C2SThreadTaskInterface *pNextTask = *( m_tasks.begin() );
        m_tasks.pop_front();

//        if ( !m_tasks.size() )
//        {
          m_detachMutex.unlock();
//        }
        m_bStartingNextTask = false;
        return pNextTask;
      }

    private:

      std::list<C2STaskQueueRunnable> m_runnables;

      std::list<C2SThreadTaskInterface*> m_tasks;

      C2SThreadQueue<C2STaskQueueRunnable> m_workers;

      volatile bool m_bIsRunning;

      volatile bool m_bStartingNextTask;

      C2SMutex m_mutex;

      C2SMutex m_runningMutex;

      C2SMutex m_detachMutex;

    };

    inline void C2STaskQueueRunnable::run()
    {
      C2SThreadTaskInterface *pTask = m_pQueue->detach();
      pTask->run();
    }

  }
}

#endif /* C2STASKQUEUE_H_ */
