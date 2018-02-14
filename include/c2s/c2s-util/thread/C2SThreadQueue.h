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

#ifndef C2STHREADQUEUE_H_
#define C2STHREADQUEUE_H_

#include "C2SLock.h"
#include "C2SMutex.h"
#include "C2SThreadBase.h"
#include "C2SThreadQueueException.h"

#include <list>
#include <cassert>

namespace c2s
{

  namespace thread
  {

    template <class Runnable> class C2SThreadQueue;

    template <class Runnable>
    class C2SThreadQueue
    {
    public:

      C2SThreadQueue();

      virtual ~C2SThreadQueue();

      void queue( Runnable *pRunnable );

      //start next available thread
      void start();

      void join();

    private:

      class C2SThreadQueueRunner : public C2SThreadBase
      {
      public:

        C2SThreadQueueRunner( Runnable *pRunnable , C2SThreadQueue<Runnable> *pQueue )
          : m_runnable( *pRunnable ),
            m_pQueue( pQueue )
        {
        };
            
        ~C2SThreadQueueRunner()
        {
          C2SLock<C2SMutex> lock( &m_mutex );
        }

        void run();

        //TODO: Exception handling
        void startThread();

      private:

        C2SThreadQueueRunner( const C2SThreadQueueRunner &r );

        C2SThreadQueueRunner &operator=( const C2SThreadQueueRunner &r );

        Runnable &m_runnable;

        C2SThreadQueue<Runnable> *m_pQueue;

        C2SMutex m_mutex;

      };

    protected:

      friend class C2SThreadQueueRunner;

      void reregister( C2SThreadQueueRunner *pRunner );

    private:

      std::list<C2SThreadQueueRunner*> m_threads;

      unsigned int m_iSize;

      C2SMutex m_writeMutex;

      C2SMutex m_occupiedMutex;

      C2SMutex m_busyMutex;

#ifdef DEBUG
      bool m_bLocked;
#endif

    };

    template <class Runnable>
    C2SThreadQueue<Runnable>::C2SThreadQueue()
      : m_iSize( 0 )
#ifdef DEBUG
        , m_bLocked( false )
#endif
    {

    }

    template <class Runnable>
    C2SThreadQueue<Runnable>::~C2SThreadQueue()
    {
      typename std::list<C2SThreadQueueRunner*>::iterator it = m_threads.begin();
      for ( ; it != m_threads.end(); ++it )
        delete ( *it );
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::queue( Runnable *pRunnable )
    {
      C2SLock<C2SMutex> writeLock( &m_writeMutex );
      ++m_iSize;
      m_threads.push_back( new C2SThreadQueueRunner( pRunnable , this ) );
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::start()
    {
      m_occupiedMutex.lock();
      //TODO
#ifdef WINXX
      while( m_threads.size() == 0 )
        ;
#endif

      C2SLock<C2SMutex> writeLock( &m_writeMutex );

#ifdef DEBUG
      assert( !m_bLocked );
      m_bLocked = true;
#endif

      if ( !m_threads.size() )
      {
#ifdef DEBUG
        m_bLocked = false;
#endif
        m_occupiedMutex.unlock();
        throw C2SThreadQueueException( "C2SThreadQueue::start: Thread queue is empty!" );
      }

      assert( m_threads.size() <= m_iSize );

      if ( m_iSize == m_threads.size() )
        m_busyMutex.lock();

      C2SThreadQueueRunner &runner = *( m_threads.front() );
      m_threads.pop_front();

      if ( m_threads.size() )
        m_occupiedMutex.unlock();

#ifdef DEBUG
      m_bLocked = false;
#endif

      runner.startThread();
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::join()
    {
      C2SLock<C2SMutex> lock( &m_busyMutex );
      //TODO
#ifdef WINXX
      while ( m_threads.size() != m_iSize )
        ;
#endif
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::reregister( C2SThreadQueueRunner *pRunner )
    {
      C2SLock<C2SMutex> writeLock( &m_writeMutex );

#ifdef DEBUG
      assert( !m_bLocked );
      m_bLocked = true;
#endif

      bool bUnlockOccupied = false;
      if ( !m_threads.size() )
        bUnlockOccupied = true;

      m_threads.push_back( pRunner );

#ifdef DEBUG
      m_bLocked = false;
#endif

      if ( bUnlockOccupied )
        m_occupiedMutex.unlock();

      if ( m_iSize == m_threads.size() )
        m_busyMutex.unlock();
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::C2SThreadQueueRunner::startThread()
    {
      m_mutex.lock();
      m_mutex.unlock();

      if ( !m_pQueue )
        throw C2SThreadQueueException( "C2SThreadQueueRunner::start: Parent thread queue is not set!" );

      this->start();
    }

    template <class Runnable>
    void C2SThreadQueue<Runnable>::C2SThreadQueueRunner::run()
    {
      C2SLock<C2SMutex> lock( &m_mutex );

      m_runnable.run();
      assert( m_pQueue );
      m_pQueue->reregister( this );
    }

  }

}

#endif /* C2STHREADQUEUE_H_ */
