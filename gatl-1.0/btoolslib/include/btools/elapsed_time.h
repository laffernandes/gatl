/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _BTOOLS_ELAPSED_TIME_
#define _BTOOLS_ELAPSED_TIME_

// The namespace of the basic tools library.
namespace btools
{

/*******************************************************************************************************
 * elapsed_time class definitions.
 *******************************************************************************************************/

// elapsed_time computes the mean elapsed time over a set of iterations.
class elapsed_time
{
private:

#ifndef NDEBUG
	// This flag helps to keep the integrity of iterations.
	bool m_running;
#endif // !NDEBUG

	// The initial time of the current iteration.
	clock_t m_begin;

	// Number of iterations.
	unsigned int m_iterations;
	
	// The sum of the elapsed time over a set of iterations.
	clock_t m_sum;

public:

	// Return the accumulated elapsed time (in seconds) over all iteractions since the initialization.
	inline
	double accumulated_elapsed_time() const
	{
#ifndef NDEBUG
		assert( !m_running );
#endif // !NDEBUG

		return static_cast<double>( m_sum ) / static_cast<double>( CLOCKS_PER_SEC );
	}

	// Default constructor.
	elapsed_time() :
#ifndef NDEBUG
		m_running( false ),
#endif // !NDEBUG
		m_begin( 0 ),
		m_iterations( 0 ),
		m_sum( 0 )
	{
	}

	// Specifies the begin of an iteration.
	inline
	void begin()
	{
#ifndef NDEBUG
		assert( !m_running );
		m_running = true;
#endif // !NDEBUG

		m_begin = clock();
	}

	// Specifies the end of an iteration.
	inline
	void end()
	{
#ifndef NDEBUG
		assert( m_running );
		m_running = false;
#endif // !NDEBUG

		m_sum += clock() - m_begin;
		++m_iterations;
	}

	// Return the mean elapsed time (in seconds) over all iteractions since the initialization.
	inline
	double mean_elapsed_time() const
	{
#ifndef NDEBUG
		assert( !m_running );
#endif // !NDEBUG

		return static_cast<double>( m_sum ) / static_cast<double>( CLOCKS_PER_SEC * m_iterations );
	}

	// Empties a previous log.
	inline
	void reset()
	{
#ifndef NDEBUG
		assert( !m_running );
#endif // !NDEBUG

		m_iterations = 0;
		m_begin = m_sum = 0;
	}
};

}

#endif // !_BTOOLS_ELAPSED_TIME_
