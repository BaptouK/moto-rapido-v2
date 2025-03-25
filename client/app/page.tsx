"use client"

import Image from 'next/image';
import { Button } from "@/components/ui/button"
import {
    Form,
    FormControl,
    FormDescription,
    FormField,
    FormItem,
    FormLabel,
    FormMessage,
} from "@/components/ui/form"
import { Input } from "@/components/ui/input"

import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";
import { useForm } from "react-hook-form";
import { useEffect, useState } from "react";

// Fonction pour lire les cookies côté client
const getCookie = (name: string) => {
    const value = `; ${document.cookie}`;
    const parts = value.split(`; ${name}=`);
    if (parts.length === 2) return parts.pop()?.split(';').shift();
    return null;
}

// Fonction pour définir un cookie côté client
const setCookie = (name: string, value: string, days: number) => {
    const date = new Date();
    date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000)); // Expire dans 'days' jours
    document.cookie = `${name}=${value}; expires=${date.toUTCString()}; path=/`;
};

const formSchema = z.object({
    username: z.string().min(3).max(20),
});

export default function Home() {
    const form = useForm<z.infer<typeof formSchema>>({
        resolver: zodResolver(formSchema),
        defaultValues: {
            username: "",
        },
    });

    useEffect(() => {
        // Récupérer le username à partir des cookies côté client
        const storedUsername = getCookie("username");
        if (storedUsername) {
            form.setValue("username", storedUsername);
        }
    }, []);

    function onSubmit(values: z.infer<typeof formSchema>) {
        // Enregistrer le username dans le cookie
        setCookie("username", values.username, 7); // Le cookie expire dans 7 jours
        // Rediriger vers la page des jeux
        window.location.href = "/games";
    }

    return (
        <div className="flex flex-col items-center justify-center h-screen">
            <Form {...form}>
                <Image
                    src="/logo.png"
                    alt="Logo"
                    width={200}
                    height={200}
                />
                <form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
                    <FormField
                        control={form.control}
                        name="username"
                        render={({ field }) => (
                            <FormItem>
                                <FormLabel>Nom</FormLabel>
                                <div className="flex items-center space-x-4">
                                    <FormControl className="flex-1">
                                        <Input placeholder="MotoRapido49_RPZ" {...field} />
                                    </FormControl>
                                    <Button type="submit" className={"cursor-pointer"}>Commencer</Button>
                                </div>
                                <FormDescription>
                                    Ceci sera votre pseudo visible par tous les joueurs.
                                </FormDescription>
                                <FormMessage />
                            </FormItem>
                        )}
                    />
                </form>
            </Form>
        </div>
    );
}
