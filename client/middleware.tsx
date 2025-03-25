import { NextResponse } from 'next/server'
import type { NextRequest } from 'next/server'

function isAuthenticated(request: NextRequest) {
    return request.cookies.has("username");
}

// This function can be marked `async` if using `await` inside
export function middleware(request: NextRequest) {
    if (!isAuthenticated(request)) {
        return NextResponse.redirect(new URL('/', request.url));
    }
}

export const config = {
    matcher: ['/game(.*)'],
};

