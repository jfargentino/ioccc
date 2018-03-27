/*		 
 * Copyright (C) 2014-2015 Sebastiano Vigna 
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 3 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */


import java.math.BigInteger;

public class XorShiftPoly116 {
	
	private XorShiftPoly116() {}
	
	/** The number of bits of state of the generator. */
	public final static int BITS = 116;
	
	/** The period of the generator (2<sup>{@value #BITS}</sup> &minus; 1). */
	public static BigInteger twoToBitsMinus1;

	/** Factors of 2<sup>{@value #BITS}</sup> &minus; - 1. */
	public static final BigInteger[] factor = {
		new BigInteger("3"),
		new BigInteger("5"),
		new BigInteger("59"),
		new BigInteger("233"),
		new BigInteger("1103"),
		new BigInteger("2089"),
		new BigInteger("3033169"),
		new BigInteger("107367629"),
		new BigInteger("536903681")
	};
	
	/** An array of cofactors. Entry 0 &le; {@code i} &lt; {@link #numCofactors} contains {@link #twoToBitsMinus1} divided by {@link #factor factor[ i ]}. Note that some
	 * entries can be {@code null} if {@link #BITS} is less then 4096. */
	public static final BigInteger[] cofactor = new BigInteger[ factor.length ];
	
	/** The actual number of valid entries in {@link #cofactor}. */
	public static int numCofactors;
	
	/** Computes the power to a given exponent, given the quadratures.
	 * 
	 * @param e an exponent smaller than or equal to 2<sup>{@link #BITS}</sup>. 
	 */
	public static void mPow( BigInteger e ) {
		System.out.println( "p := 1;" );
		for( int i = 0; ! e.equals( BigInteger.ZERO ); i++ ) {
			if ( e.testBit( 0 ) ) System.out.println( "p := *p * q[" + i + "];" );
			e = e.shiftRight( 1 );
		}
	}
	
	public static void main( final String arg[] ) {
		BigInteger result = BigInteger.ONE;
		twoToBitsMinus1 = BigInteger.valueOf( 2 ).pow( BITS ).subtract( BigInteger.ONE );
		int n;
		// Initialize cofactors.
		for( n = 0; n < factor.length; n++ ) {
			cofactor[ n ] = twoToBitsMinus1.divide( factor[ n ] );
			result = result.multiply( factor[ n ] );
		}

		// Safety check (you know, those numbers are LONG).
		if ( ! twoToBitsMinus1.equals( result ) ) throw new AssertionError();

		System.out.println( "Array q[" + ( BITS + 1 ) + "];" );
		// Quadratures
		System.out.println( "q[0] := x;" );
		for( int i1 = 1; i1 <= BITS; i1++ ) System.out.println( "q[" + i1 + "] := q[" + ( i1 - 1 ) + "] * q[" + ( i1 - 1 ) + "];" );
		System.out.println( "!!('Check: ', if q[" + BITS + "] = x then 1 else 0; &q fi);" );
		// Exponentiation to cofactors
		for( int i = 0; i < cofactor.length; i++ ) {
			mPow( cofactor[ i ] );
			System.out.println( "!!('Result: ', if p = 1 then 0; &q else 1 fi);");
		}
	}
}
