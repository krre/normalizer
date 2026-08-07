import { sveltekit } from '@sveltejs/kit/vite';
import { defineConfig } from 'vitest/config';

export default defineConfig({
	plugins: [
		sveltekit(),
		{
			name: 'wasm-reload',
			handleHotUpdate({ file, server }) {
				if (file.endsWith('.wasm')) {
					server.ws.send({
						type: 'full-reload',
						path: '*'
					})
				}
			}
		}
	],
	test: {
		include: ['src/**/*.{test,spec}.{js,ts}']
	}
});
